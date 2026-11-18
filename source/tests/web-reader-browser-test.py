#!/usr/bin/env python3
"""Real CGI/CSS layout checks. Requires Chromium and Python websocket-client."""
from contextlib import contextmanager
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import base64
import json
import mimetypes
import os
import shutil
import subprocess
import sys
import tempfile
import threading
import time
from urllib.request import urlopen
from urllib.parse import urlsplit

import websocket

ROOT = Path(__file__).resolve().parents[2]
CGI = Path(sys.argv[1]).resolve()
CHROME = shutil.which('chromium') or shutil.which('chromium-browser')
if not CHROME:
    raise SystemExit('Chromium is required for this optional browser check')


class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        url = urlsplit(self.path)
        if url.path in ('/cgi-bin/l.cgi', '/native.cgi'):
            data = subprocess.check_output([str(CGI)], cwd=ROOT / 'source', timeout=30,
                env=dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=url.query)).split(b'\n\n', 1)[1]
            if url.path == '/native.cgi':
                # Native exports have no web marker; exercise the shared CSS too.
                data = data.replace(b' class="web-reader"', b'')
            kind = 'text/html; charset=utf-8'
        else:
            path = (ROOT / url.path.lstrip('/')).resolve()
            if not path.is_relative_to(ROOT) or not path.is_file():
                self.send_error(404)
                return
            data = path.read_bytes()
            kind = mimetypes.guess_type(path)[0] or 'application/octet-stream'
        self.send_response(200)
        self.send_header('Content-Type', kind)
        self.send_header('Content-Length', str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def log_message(self, *args):
        pass


class Browser:
    def __init__(self, connection):
        self.ws, self.request = connection, 0

    def call(self, method, **params):
        self.request += 1
        self.ws.send(json.dumps(dict(id=self.request, method=method, params=params)))
        while True:
            message = json.loads(self.ws.recv())
            if message.get('id') == self.request:
                assert 'error' not in message, message
                return message.get('result', {})

    def js(self, expression):
        result = self.call('Runtime.evaluate', expression=expression, returnByValue=True, awaitPromise=True)
        assert 'exceptionDetails' not in result, result
        return result['result'].get('value')

    def settle(self):
        self.js('new Promise(resolve => requestAnimationFrame(() => requestAnimationFrame(resolve)))')

    def until(self, expression):
        for _ in range(250):
            if self.js(expression):
                return
            time.sleep(0.02)
        raise AssertionError('Timed out: ' + expression)

    def width(self, width):
        self.call('Emulation.setDeviceMetricsOverride', width=width, height=900, deviceScaleFactor=1, mobile=False)
        self.settle()

    def open(self, query, width=1920, native=False):
        self.width(width)
        address = f'http://127.0.0.1:{server.server_port}' + ('/native.cgi?' if native else '/cgi-bin/l.cgi?')
        self.js('window.leavingTestPage = true')
        self.call('Page.navigate', url=address + query)
        for _ in range(200):
            if self.js("!window.leavingTestPage && document.readyState === 'complete' && !!document.getElementById('contentRoot')"):
                break
            time.sleep(0.02)
        else:
            raise AssertionError('CGI page did not finish loading')
        self.js('document.fonts.ready.then(() => true)')
        self.settle()

    def geometry(self):
        return self.js('''(() => {
          const root = document.getElementById('contentRoot');
          const rect = element => {
            const r = element.getBoundingClientRect();
            return {left:r.left, right:r.right, width:r.width, height:r.height};
          };
          return {root:rect(root), body:rect(document.body),
            maximum:getComputedStyle(root).maxWidth,
            viewport:document.documentElement.clientWidth,
            scrollWidth:document.documentElement.scrollWidth};
        })()''')

    def screenshot(self, name):
        folder = os.environ.get('BREVIAR_BROWSER_PREVIEWS')
        if folder:
            path = Path(folder)
            path.mkdir(parents=True, exist_ok=True)
            image = self.call('Page.captureScreenshot', format='png')
            (path / (name + '.png')).write_bytes(base64.b64decode(image['data']))

    def menu(self, right=False, opened=True):
        self.js(('disableNavL(); enableNavR(); ' if right else 'disableNavR(); enableNavL(); ')
                + (('openNavR()' if right else 'openNav()') if opened
                   else ('closeNavR()' if right else 'closeNav()')))
        self.js('new Promise(resolve => setTimeout(resolve, 600))')
        self.settle()


@contextmanager
def browser():
    with tempfile.TemporaryDirectory(prefix='breviar-reader-browser-') as profile:
        process = subprocess.Popen([CHROME, '--headless', '--no-sandbox', '--disable-gpu',
            '--disable-dev-shm-usage', '--disable-background-networking', '--remote-debugging-port=0',
            '--disable-background-timer-throttling', '--user-data-dir=' + profile, 'about:blank'],
            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        try:
            port_file = Path(profile) / 'DevToolsActivePort'
            for _ in range(200):
                if port_file.exists():
                    break
                time.sleep(0.02)
            port = port_file.read_text().splitlines()[0]
            with urlopen(f'http://127.0.0.1:{port}/json/list') as response:
                page = next(p for p in json.load(response) if p['type'] == 'page')
            connection = websocket.create_connection(page['webSocketDebuggerUrl'], timeout=30, suppress_origin=True)
            try:
                yield Browser(connection)
            finally:
                connection.close()
        finally:
            process.terminate()
            process.wait(timeout=10)


def close_enough(left, right):
    assert abs(left - right) < 1, (left, right)


server = ThreadingHTTPServer(('127.0.0.1', 0), Handler)
threading.Thread(target=server.serve_forever, daemon=True).start()
PRAYER = 'qt=pdt&d=13&m=11&r=2026&p=mv&j=sk&o0=533123'
try:
    with browser() as page:
        for width in (1920, 1040, 390):
            for margin in (0, 25):
                page.open(PRAYER + f'&mm={margin}', width)
                g = page.geometry()
                close_enough(g['root']['left'] + g['root']['right'], g['body']['left'] + g['body']['right'])
                assert g['root']['width'] <= float(g['maximum'].removesuffix('px')) + 1, g
                if g['scrollWidth'] > g['viewport']:
                    offenders = page.js('''Array.from(document.querySelectorAll('#contentRoot *')).filter(e => {
                      const r = e.getBoundingClientRect();
                      return r.width > 0 && r.right > document.documentElement.clientWidth + 1;
                    }).slice(0, 12).map(e => [e.tagName, e.className, e.textContent.slice(0, 55), e.getBoundingClientRect().right])''')
                    raise AssertionError((g, offenders))
                if width == 1920:
                    assert g['root']['width'] < width * 0.6, g
                else:
                    assert g['root']['width'] <= g['body']['width'] + 1, g
                if margin:
                    close_enough(g['body']['left'], margin)
                left = page.js("document.getElementById('myOpenbtnL').getBoundingClientRect().left")
                close_enough(left, 16)
        for query in ('qt=pdt&d=*&m=11&r=2026', 'qt=pdt&d=*&m=*&r=2026'):
            page.open(query)
            g = page.geometry()
            assert g['maximum'] == 'none', g
            close_enough(g['root']['width'], g['body']['width'])
        page.open(PRAYER.replace('o0=533123', 'o0=0'))
        assert page.geometry()['root']['width'] < 1000
        page.call('Emulation.setEmulatedMedia', media='print')
        assert page.geometry()['maximum'] == 'none'
        page.call('Emulation.setEmulatedMedia', media='screen')
        page.open(PRAYER, native=True)
        assert page.geometry()['maximum'] == 'none'

        # Avoid only actual collisions, retain exactly the same text measure.
        for width in (1920, 1040, 800, 390):
            for right in (False, True):
                page.open(PRAYER + '&mm=25', width)
                original = page.geometry()['root']
                page.js('window.scrollTo(0, 1000)')
                scroll = page.js('window.scrollY')
                page.menu(right)
                g = page.geometry()
                close_enough(g['root']['width'], original['width'])
                close_enough(g['root']['height'], original['height'])
                close_enough(page.js('window.scrollY'), scroll)
                if width >= 1000:
                    edge = page.js("document.getElementById('mySidebarR').getBoundingClientRect().left"
                                   if right else "document.getElementById('mySidebar').getBoundingClientRect().right")
                    gap = edge - g['root']['right'] if right else g['root']['left'] - edge
                    assert gap >= 15.5, (width, right, g, edge)
                    if width == 1920:
                        close_enough(g['root']['left'], original['left'])
                    elif right:
                        close_enough(g['root']['right'], edge - 16)
                    else:
                        close_enough(g['root']['left'], edge + 16)
                else:
                    close_enough(g['root']['left'], original['left'])
                if width == 1040:
                    page.screenshot('drawer-right' if right else 'drawer-left')
                page.menu(right, opened=False)
                close_enough(page.geometry()['root']['left'], original['left'])

        # Resizing and changing fonts while a drawer is open must re-evaluate fit.
        page.open(PRAYER, 1040)
        page.menu()
        for width in (1920, 800, 390, 1040):
            page.width(width)
            g = page.geometry()
            if width == 1040:
                close_enough(g['root']['left'], 236)
            else:
                close_enough(g['root']['left'] + g['root']['right'], g['body']['left'] + g['body']['right'])
        page.js("document.body.style.fontSize = '32px'")
        page.settle()
        g = page.geometry()
        close_enough(g['root']['width'], g['body']['width'])
        page.js("document.body.style.fontSize = '18px'")
        page.settle()
        close_enough(page.geometry()['root']['left'], 236)
        page.call('Emulation.setEmulatedMedia', media='print')
        close_enough(page.geometry()['root']['width'], page.geometry()['body']['width'])
        page.call('Emulation.setEmulatedMedia', media='screen')
        page.settle()
        close_enough(page.geometry()['root']['left'], 236)
        page.open(PRAYER, 1040, native=True)
        original = page.geometry()['root']
        page.menu()
        close_enough(page.geometry()['root']['left'], original['left'])

        # Sharing follows both default themes and user-selected reader palettes.
        # With a drawer, the browser stores the theme in sessionStorage; o2's
        # night-mode bit selects the corresponding server-rendered palette.
        schemes = (
            ('day', '&o2=29432', 'rgb(255, 255, 255)', 'rgb(26, 26, 26)'),
            ('night', '&o2=29688', 'rgb(0, 0, 0)', 'rgb(204, 204, 204)'),
            ('custom-day', '&o2=29432&c0=fff4dd&ct0=102030', 'rgb(255, 244, 221)', 'rgb(16, 32, 48)'),
            ('custom-night', '&o2=29688&c1=102030&ct1=f0e0c0', 'rgb(16, 32, 48)', 'rgb(240, 224, 192)'),
        )
        for name, query, background, foreground in schemes:
            page.js("sessionStorage.setItem('nightMode', true)" if name.endswith('night')
                    else "sessionStorage.removeItem('nightMode')")
            page.open(PRAYER + query, 700)
            page.until('getComputedStyle(document.body).backgroundColor === ' + json.dumps(background))
            page.js("openNav(); document.querySelector('.prayer-share-action').click()")
            page.until("!!document.querySelector('#prayer-share-panel:not([hidden]) svg')")
            colors = page.js('''(() => {
              const panel = document.getElementById('prayer-share-panel');
              const style = selector => getComputedStyle(panel.querySelector(selector));
              return {background:style('.prayer-share-window').backgroundColor,
                toolbar:style('.prayer-share-toolbar').backgroundColor,
                text:style('.prayer-share-body p').color, button:style('.prayer-share-copy').color,
                close:style('.prayer-share-close').color, credit:style('.prayer-share-attribution').color,
                qrBackground:style('rect').fill, qrForeground:style('path').fill,
                aboveDrawer:!!document.elementFromPoint(100, 100).closest('.prayer-share-panel')};
            })()''')
            assert colors['background'] == background and colors['toolbar'] == background, (name, colors)
            assert all(colors[key] == foreground for key in ('text', 'button', 'close', 'credit')), (name, colors)
            assert colors['qrBackground'] == 'rgb(255, 255, 255)' and colors['qrForeground'] == 'rgb(0, 0, 0)', colors
            assert colors['aboveDrawer'], colors
            page.screenshot('sharing-' + name)
            page.js("document.querySelector('.prayer-share-close').click()")

        # Session-only theme changes update an already-open dialog without a reload.
        page.js("sessionStorage.removeItem('nightMode')")
        page.open(PRAYER, 700)
        page.js("document.querySelector('.prayer-share-action').click()")
        page.until("!!document.querySelector('#prayer-share-panel:not([hidden]) svg')")
        page.js("sessionStorage.setItem('nightMode', true); updateNightMode()")
        page.until("getComputedStyle(document.querySelector('.prayer-share-window')).backgroundColor === 'rgb(0, 0, 0)'")
        page.js("sessionStorage.removeItem('nightMode'); updateNightMode()")
        page.until("getComputedStyle(document.querySelector('.prayer-share-window')).backgroundColor === 'rgb(255, 255, 255)'")
finally:
    server.shutdown()
print('Web reader browser checks passed: layout, drawers, resizing, fonts, margins, print, native CSS scope and sharing palettes')
