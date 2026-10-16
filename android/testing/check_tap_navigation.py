#!/usr/bin/env python3
"""Exercise the shipped script using trusted mouse/touch input in Chromium.

Requires Chromium and Python websocket-client. No Android bridge or DOM mocks:
only the Java endpoint is replaced with a recorder. Native lifetime checks are
covered by TapNavigationTest. Run with `make -C android/testing taps`.
"""
import json
import os
from pathlib import Path
import subprocess
import tempfile
import time
import urllib.request
import websocket

SCRIPT = Path(__file__).resolve().parents[1] / "assets/tap-navigation.js"
HTML = """<!doctype html><meta name="viewport" content="width=device-width,initial-scale=1">
<style>body{margin:0;height:4000px} #control{position:fixed;top:60px;left:10px;width:230px}
#text{position:fixed;top:400px;left:20px} #target{min-height:40px;display:block}</style>
<script>
window.calls=[]; window.actions=0; window.initialized=false;
window.fixtureId='FIXTURE';
window.configuration={enabled:true,token:'page1',touchSlop:8,doubleTapSlop:100,
 doubleTapTimeout:120,longPressTimeout:250,fullscreen:true};
window.tapNavigation={settings:()=>JSON.stringify(configuration),
 ready:()=>initialized=true,begin:()=>{},
 perform:(token,id,action)=>calls.push({token,id,action})};
</script><script src="SCRIPT"></script>
<div id="control">CONTROL</div><p id="text">Some selectable prayer text.</p>
<script>SETUP</script>
"""


class Browser:
    def __init__(self, ws):
        self.socket = websocket.create_connection(ws, suppress_origin=True, timeout=10)
        self.serial = 0
        self.horizontal = False

    def command(self, method, **params):
        self.serial += 1
        self.socket.send(json.dumps(dict(id=self.serial, method=method, params=params)))
        while True:
            reply = json.loads(self.socket.recv())
            if reply.get("id") == self.serial:
                assert "error" not in reply, reply
                return reply.get("result", {})

    def js(self, expression):
        reply = self.command("Runtime.evaluate", expression=expression,
                             returnByValue=True, awaitPromise=True)
        assert "exceptionDetails" not in reply, reply
        return reply.get("result", {}).get("value")

    def wait(self, ms=150):
        self.js("new Promise(resolve=>setTimeout(resolve,%d))" % ms)

    def mouse(self, kind, x=400, y=500, **extra):
        if self.horizontal:
            x, y = y, x
        return self.command("Input.dispatchMouseEvent", type=kind, x=x, y=y,
                            button="left", **extra)

    def click(self, x=400, y=500, count=1):
        self.mouse("mousePressed", x, y, clickCount=count)
        self.mouse("mouseReleased", x, y, clickCount=count)

    def touch(self, kind, x=400, y=500):
        if self.horizontal:
            x, y = y, x
        self.command("Input.dispatchTouchEvent", type=kind, touchPoints=[] if kind in
                     ("touchEnd", "touchCancel") else [dict(x=x, y=y, id=1)])


def run(browser, directory, horizontal):
    passed = 0
    # Express the shared cases in top/bottom coordinates; transpose both the
    # input and fixture for left/right mode to exercise the same protections.
    browser.horizontal = horizontal
    html = HTML.replace("enabled:true,", "enabled:true,horizontal:" + str(horizontal).lower() + ",")
    if horizontal:
        html = html.replace("top:60px;left:10px", "top:10px;left:60px")
        html = html.replace("top:400px;left:20px", "top:20px;left:400px")

    def fresh(control="", setup=""):
        page = directory / "page.html"
        identity = str(time.monotonic_ns())
        page.write_text(html.replace("SCRIPT", SCRIPT.as_uri()).replace("CONTROL", control)
                        .replace("SETUP", setup).replace("FIXTURE", identity))
        browser.command("Page.navigate", url=page.as_uri() + "?case=" + identity)
        deadline = time.monotonic() + 5
        while not browser.js("window.initialized === true && window.fixtureId === " +
                             json.dumps(identity) + " && document.readyState === 'complete'"):
            assert time.monotonic() < deadline, "Script did not initialize"
            time.sleep(.01)
        browser.js("new Promise(resolve=>requestAnimationFrame(()=>requestAnimationFrame(resolve)))")

    def expect(actions, name):
        nonlocal passed
        browser.wait()
        calls = browser.js("calls.map(call=>call.action)")
        assert calls == actions, (name, calls, actions, browser.js("getSelection().toString()"))
        passed += 1
        print("PASS", "left/right" if horizontal else "top/bottom", name, flush=True)

    for y, action in ((100, "up"), (300, None), (500, "down")):
        fresh()
        browser.click(y=y)
        expect([action] if action else [], "mouse third " + str(y))
        fresh()
        browser.touch("touchStart", y=y)
        browser.touch("touchEnd")
        expect([action] if action else [], "touch third " + str(y))

    for y, action in ((100, "up"), (500, "down")):
        fresh(setup="configuration.doubleTapTimeout=2000;BreviarTaps.configure()")
        browser.touch("touchStart", y=y)
        browser.touch("touchEnd")
        # The bridge must be called well before even a long double-tap deadline.
        expect([action], "immediate outer-third tap " + str(y))
        browser.touch("touchStart", y=y)
        browser.touch("touchEnd")
        expect([action, action], "repeated outer taps page independently " + str(y))

    controls = [
        ('<a id="target" href="#anchor"><span>Calendar / footnote link</span></a>', "", 0),
        ('<button id="target" onclick="actions++"><span>TTS settings</span></button>', "", 1),
        ('<button id="target" disabled>Disabled</button>', "", 0),
        ('<input id="target" type="text">', "", 0),
        ('<label id="target" for="check">Checkbox label</label><input id="check" type="checkbox">', "", 0),
        ('<div id="target" contenteditable>Editable</div>', "", 0),
        ('<details><summary id="target">Details</summary>More text</details>', "", 0),
        ('<div id="target" data-breviar-interactive><span>Custom control</span></div>', "", 0),
        ('<div id="target" onclick="actions++">Inline handler</div>', "", 1),
        ('<div id="target">Property handler</div>', 'target.onclick=()=>actions++;', 1),
        ('<div id="target">Claimed listener</div>',
         "target.addEventListener('click',e=>{BreviarTaps.claim(e);actions++});", 1),
        ('<div id="target"><span>Delegated action</span></div>',
         "document.addEventListener('click',e=>{if(e.target.closest('#target')){BreviarTaps.claim(e);actions++}});", 1),
        ('<div id="target">Asynchronous action</div>',
         "target.addEventListener('click',e=>{BreviarTaps.claim(e);setTimeout(()=>actions++,180)});", None),
        ('<div id="target">Canceled click</div>',
         "target.addEventListener('click',e=>{e.preventDefault();actions++});", 1),
        ('<div id="target">Stopped click</div>',
         "target.addEventListener('click',e=>{e.stopPropagation();actions++});", 1),
        ('<div id="target">Claimed touch start</div>',
         "target.addEventListener('touchstart',e=>{BreviarTaps.claim(e);actions++});", 1),
    ]
    for i, (markup, setup, expected) in enumerate(controls):
        fresh(markup, setup)
        browser.touch("touchStart", 40, 80)
        browser.touch("touchEnd")
        expect([], "interactive element " + str(i))
        if expected is not None:
            assert browser.js("actions") == expected, (i, "HTML action was lost")

    fresh()
    browser.touch("touchStart", y=300)
    browser.touch("touchEnd")
    browser.wait(30)
    browser.touch("touchStart", y=300)
    browser.touch("touchEnd")
    expect(["fullscreen"], "middle-third double tap, no intermediate page")

    fresh()
    browser.touch("touchStart", y=300)
    browser.touch("touchEnd")
    browser.wait(30)
    browser.js("BreviarTaps.configure();BreviarTaps.configure()")
    browser.touch("touchStart", y=300)
    browser.touch("touchEnd")
    expect(["fullscreen"], "repeated readiness requests preserve pending double tap")

    fresh()
    browser.touch("touchStart", y=500)
    browser.js("BreviarTaps.configure()")
    browser.touch("touchEnd")
    expect(["down"], "repeated readiness request preserves current touch")

    fresh()
    browser.js("window.stale={...configuration,enabled:false,token:'old'};"
               "configuration.token='current';BreviarTaps.configure();BreviarTaps.configure(stale)")
    browser.touch("touchStart", y=500)
    browser.touch("touchEnd")
    expect(["down"], "late configuration reads current settings instead of stale snapshot")
    assert browser.js("calls[0].token") == "current"

    for first, second, actions in ((190, 210, ["up"]), (210, 190, ["up"]),
                                    (390, 410, ["down"]), (410, 390, ["down"])):
        fresh()
        browser.touch("touchStart", y=first)
        browser.touch("touchEnd")
        browser.wait(30)
        browser.touch("touchStart", y=second)
        browser.touch("touchEnd")
        expect(actions, "cross-third taps never toggle fullscreen " + str((first, second)))

    fresh('<button id="target" onclick="actions++">Action</button>')
    browser.click(40, 80)
    browser.wait(30)
    browser.click(40, 80, count=2)
    expect([], "double tap on control")
    assert browser.js("actions") == 2

    fresh()
    browser.click(y=300)
    browser.wait(30)
    browser.js("configuration.token='page2';BreviarTaps.configure()")
    browser.click(y=300)
    expect([], "new document token cancels pending middle tap")

    fresh()
    browser.click(y=300)
    browser.wait(30)
    browser.js("configuration.enabled=false;BreviarTaps.configure()")
    browser.click(y=300)
    expect([], "mode change cancels pending middle tap")

    fresh()
    browser.click(300, 300)
    browser.wait(30)
    browser.js("configuration.horizontal=!configuration.horizontal;BreviarTaps.configure()")
    browser.click(300, 300)
    expect([], "axis change cancels pending middle tap")

    fresh()
    browser.click(y=300)
    browser.wait(30)
    browser.js("window.scrollTo(0,300)")
    browser.wait(30)
    browser.click(y=300)
    expect([], "scroll cancels pending middle tap")

    fresh()
    browser.mouse("mousePressed")
    browser.mouse("mouseMoved", 400, 440, buttons=1)
    browser.mouse("mouseReleased", 400, 440, clickCount=1)
    expect([], "drag")

    fresh()
    browser.touch("touchStart")
    browser.wait(280)
    browser.touch("touchEnd")
    expect([], "long press")

    fresh()
    browser.touch("touchStart")
    browser.touch("touchCancel")
    expect([], "canceled touch")

    fresh()
    browser.touch("touchStart")
    browser.command("Input.dispatchTouchEvent", type="touchStart",
                    touchPoints=[dict(x=400,y=500,id=1), dict(x=450,y=500,id=2)])
    browser.command("Input.dispatchTouchEvent", type="touchMove",
                    touchPoints=[dict(x=380,y=500,id=1), dict(x=470,y=500,id=2)])
    browser.touch("touchEnd")
    expect([], "multiple fingers / pinch")

    fresh()
    browser.touch("touchStart")
    browser.touch("touchMove", 400, 300)
    browser.touch("touchEnd")
    expect([], "touch scrolling")

    fresh()
    browser.js("let range=document.createRange();range.selectNodeContents(text);getSelection().removeAllRanges();getSelection().addRange(range)")
    browser.click()
    expect([], "tap clearing text selection")

    fresh()
    browser.click(y=300)
    browser.wait(30)
    browser.js("let range=document.createRange();range.selectNodeContents(text);getSelection().removeAllRanges();getSelection().addRange(range)")
    browser.click(y=300)
    expect([], "selection cancels pending middle tap")

    fresh('<button id="target" onclick="actions++">Action</button>')
    browser.js("target.focus()")
    browser.command("Input.dispatchKeyEvent", type="keyDown", key="Enter", code="Enter", windowsVirtualKeyCode=13,
                    text="\r", unmodifiedText="\r")
    browser.command("Input.dispatchKeyEvent", type="keyUp", key="Enter", code="Enter", windowsVirtualKeyCode=13)
    expect([], "keyboard activation")
    assert browser.js("actions") == 1

    fresh()
    browser.js("document.body.dispatchEvent(new MouseEvent('mousedown',{bubbles:true,clientX:400,clientY:500}));"
               "document.body.dispatchEvent(new MouseEvent('mouseup',{bubbles:true,clientX:400,clientY:500}));"
               "document.body.dispatchEvent(new MouseEvent('click',{bubbles:true,clientX:400,clientY:500}))")
    expect([], "programmatic events")

    fresh()
    browser.js("control.innerHTML='<button id=target onclick=actions++>Dynamic</button>'")
    browser.click(40, 80)
    expect([], "dynamically inserted control")
    assert browser.js("actions") == 1

    fresh()
    browser.js("configuration.fullscreen=false;BreviarTaps.configure()")
    browser.touch("touchStart", y=300)
    browser.touch("touchEnd")
    browser.wait(30)
    browser.touch("touchStart", y=300)
    browser.touch("touchEnd")
    expect([], "HTML dialog middle double tap does nothing")

    fresh()
    browser.js("window.scrollTo(0,900)")
    browser.wait(30)
    browser.touch("touchStart", 400, 100)
    browser.touch("touchEnd")
    expect(["up"], "thirds are relative to viewport after scrolling")

    # A non-square viewport catches using height instead of width in left/right
    # mode (and the converse). Use the selected axis's 900-pixel dimension.
    browser.command("Emulation.setDeviceMetricsOverride", width=900 if horizontal else 600,
                    height=600 if horizontal else 900, deviceScaleFactor=1, mobile=True)
    for position, action in ((250, "up"), (350, None), (550, None), (650, "down")):
        fresh()
        browser.touch("touchStart", x=400, y=position)
        browser.touch("touchEnd")
        expect([action] if action else [], "non-square viewport third " + str(position))
    browser.command("Emulation.setDeviceMetricsOverride", width=600, height=600,
                    deviceScaleFactor=1, mobile=True)

    print("Passed", passed, "Chromium tap-navigation cases", flush=True)


def main():
    with tempfile.TemporaryDirectory(prefix="breviar-taps-") as tmp:
        directory = Path(tmp)
        profile = directory / "profile"
        with (directory / "chromium.log").open("w") as log:
            process = subprocess.Popen([os.environ.get("CHROMIUM", "/usr/bin/chromium"),
                "--headless", "--no-sandbox", "--disable-gpu", "--no-first-run",
                "--remote-debugging-port=0", "--user-data-dir=" + str(profile), "about:blank"],
                stdout=log, stderr=log)
            browser = None
            try:
                deadline = time.monotonic() + 10
                while not (profile / "DevToolsActivePort").exists():
                    assert process.poll() is None, (directory / "chromium.log").read_text()
                    assert time.monotonic() < deadline, "Chromium startup timed out"
                    time.sleep(.02)
                port = (profile / "DevToolsActivePort").read_text().splitlines()[0]
                with urllib.request.urlopen("http://127.0.0.1:" + port + "/json") as response:
                    tabs = json.load(response)
                browser = Browser(next(tab["webSocketDebuggerUrl"] for tab in tabs if tab["type"] == "page"))
                browser.command("Page.enable")
                browser.command("Emulation.setDeviceMetricsOverride", width=600, height=600,
                                deviceScaleFactor=1, mobile=True)
                browser.command("Emulation.setTouchEmulationEnabled", enabled=True)
                run(browser, directory, horizontal=False)
                run(browser, directory, horizontal=True)
            finally:
                if browser:
                    browser.socket.close()
                process.terminate()
                process.wait(timeout=10)


if __name__ == "__main__":
    main()
