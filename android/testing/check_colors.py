#!/usr/bin/env python3
"""Check real browser colors, including generated symbols and unchanged defaults."""
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from html import unescape

ROOT = Path(__file__).resolve().parents[2]
BROWSER = shutil.which('chromium') or shutil.which('chromium-browser')
if not BROWSER:
    raise SystemExit('Chromium is required for this optional browser check')

sample = '''
<p id="text">Text <a id="link" href="#">link</a></p>
<h2 id="heading">Heading</h2>
<p class="red" id="rubric">Rubric <a class="quiet" id="reference" href="#">reference</a></p>
<p class="antiphon ant" id="antiphon">Antiphon</p>
<p class="respF" id="response">Response</p>
<div class="respons">
  <p class="respR" id="response-r">Response R</p>
  <p class="respV" id="response-v">Verse V</p>
  <p class="respS" id="response-s">Response S</p>
  <p class="respO" id="response-o">Response O</p>
</div>
<p class="antiphon first-ant" id="antiphon-first">First antiphon</p>
<p class="antiphon second-ant" id="antiphon-second">Second antiphon</p>
<p class="antiphon third-ant" id="antiphon-third">Third antiphon</p>
<p class="antiphon ant-first" id="antiphon-sk-first">First Slovak antiphon</p>
<p class="antiphon ant-second" id="antiphon-sk-second">Second Slovak antiphon</p>
<p class="antiphon ant-third" id="antiphon-sk-third">Third Slovak antiphon</p>
<p class="reading-title" id="reading">Reading</p>
<div class="psalm"><p class="psalm-name" id="psalm">Psalm</p></div>
<sup id="verse">1</sup>
<div class="sidebar"><a id="drawer" href="#">Drawer</a></div>
<script>
const colors = {};
for (const id of ['text', 'link', 'heading', 'rubric', 'reference', 'reading', 'psalm', 'verse', 'drawer'])
  colors[id] = getComputedStyle(document.getElementById(id)).color;
for (const id of ['antiphon', 'response', 'response-r', 'response-v', 'response-s', 'response-o',
                 'antiphon-first', 'antiphon-second', 'antiphon-third',
                 'antiphon-sk-first', 'antiphon-sk-second', 'antiphon-sk-third'])
  colors[id] = getComputedStyle(document.getElementById(id), '::before').color;
colors.responseWeight = getComputedStyle(document.getElementById('response-r'), '::before').fontWeight;
colors.background = getComputedStyle(document.body).backgroundColor;
document.body.insertAdjacentHTML('beforeend', '<pre id="result">' + JSON.stringify(colors) + '</pre>');
</script>'''


def computed(css, overrides=''):
    with tempfile.TemporaryDirectory(prefix='breviar-colors-') as directory:
        path = Path(directory)
        page = path / 'test.html'
        page.write_text('<!doctype html><html style="' + overrides + '"><head><style>'
                        + css + '</style></head><body>' + sample + '</body></html>')
        result = subprocess.run([BROWSER, '--headless', '--no-sandbox', '--disable-gpu',
            '--disable-dev-shm-usage', '--disable-background-networking',
            '--host-resolver-rules=MAP * ~NOTFOUND', '--user-data-dir=' + str(path / 'profile'),
            '--dump-dom', page.as_uri()], check=True, capture_output=True, text=True, timeout=40)
        return json.loads(unescape(re.search(r'<pre id="result">(\{.*?)</pre>', result.stdout).group(1)))


base = (ROOT / 'breviar.css').read_text()
night = (ROOT / 'breviar-invert-colors.css').read_text()
normal_font = (ROOT / 'breviar-normal-font.css').read_text()
variants = [(mode + '/' + weight, css + override)
            for mode, css in [('day', base), ('night', base + night)]
            for weight, override in [('bold', ''), ('normal', normal_font)]]
for mode, css in variants:
    defaults = computed(css)
    # Every new var() declaration has the original literal immediately before it.
    original = re.sub(r'[\w-]+\s*:[^;{}]*var\(--prayer-[^;{}]+;', '', css)
    assert defaults == computed(original), (mode, 'Defaults changed')
    assert defaults['responseWeight'] == ('400' if mode.endswith('/normal') else '700'), (mode, defaults)
    custom = computed(css, '--prayer-text: #123456; --prayer-rubric: #abcdef; --prayer-background: #102030;')
    for key in ('text', 'link', 'heading'):
        assert custom[key] == 'rgb(18, 52, 86)', (mode, key, custom)
    for key in ('rubric', 'reference', 'antiphon', 'response', 'reading', 'psalm', 'verse',
                'response-r', 'response-v', 'response-s', 'response-o',
                'antiphon-first', 'antiphon-second', 'antiphon-third',
                'antiphon-sk-first', 'antiphon-sk-second', 'antiphon-sk-third'):
        assert custom[key] == 'rgb(171, 205, 239)', (mode, key, custom)
    assert custom['background'] == 'rgb(16, 32, 48)', custom
    assert custom['drawer'] == defaults['drawer'], 'Reading colors leaked into the web drawer'
    if mode.startswith('day/'):
        contrast = computed(css, '--prayer-text: #000000; --prayer-rubric: #800000; --prayer-background: #ffffff;')
        for key in ('text', 'link', 'heading'):
            assert contrast[key] == 'rgb(0, 0, 0)', (mode, key, contrast)
        for key in ('rubric', 'reference', 'response-r', 'response-v', 'antiphon'):
            assert contrast[key] == 'rgb(128, 0, 0)', (mode, key, contrast)
        assert contrast['background'] == 'rgb(255, 255, 255)', (mode, contrast)
print('Browser color checks passed for day/night palettes with bold/normal text')
