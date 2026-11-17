#!/usr/bin/env python3
"""Exercise the actual CGI and sharing JavaScript in a short browser viewport."""
from html import unescape
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import base64
import io
import json
import mimetypes
import os
import re
import shutil
import subprocess
import sys
import tempfile
import threading
from urllib.parse import parse_qs, urlsplit

from PIL import Image, ImageChops
import zxingcpp

ROOT = Path(__file__).resolve().parents[2]
CGI = Path(sys.argv[1]).resolve()
ENCODER = Path(sys.argv[2]).resolve() if len(sys.argv) > 2 else ROOT / 'source/.test-build/prayer-sharing-test'
BROWSER = shutil.which('chromium') or shutil.which('chromium-browser')
if not BROWSER:
    raise SystemExit('Chromium is required for this optional browser check')

CHECK = r'''
(async function () {
  const result = {};
  try {
    const wait = async check => {
      for (let i = 0; i < 500; ++i) {
        if (check()) return;
        await new Promise(resolve => setTimeout(resolve, 20));
      }
      throw new Error('Timed out waiting for sharing UI');
    };
    const require = (value, message) => { if (!value) throw new Error(message); };
    let copied;
    Object.defineProperty(navigator, 'clipboard', {value: {
      writeText: text => { copied = text; return Promise.resolve(); }
    }});
    const metadata = document.getElementById('prayer-share-panel');
    const base = metadata.getAttribute('data-url');
    const fragment = encodeURIComponent('Zdravas’, Mária + 20%');
    history.replaceState(history.state, '', location.pathname + location.search + '#' + fragment);
    let expected = base + '#' + fragment;
    require(!metadata.querySelector('svg'), 'Normal page encoded a QR');
    // Use the actual menu handler with a visible menu entry.
    const link = document.querySelector('.prayer-share-action');
    for (let p = link.parentElement; p !== document.body; p = p.parentElement)
      p.style.display = 'block';
    const shareIcon = link.querySelector('.prayer-share-menu-icon');
    require(shareIcon && shareIcon.getBoundingClientRect().width > 0, 'Share icon is missing');
    require(getComputedStyle(shareIcon).backgroundColor === getComputedStyle(link).color,
      'Share icon does not follow the menu color');
    const asset = new Image();
    asset.src = '/share-icon.png';
    await asset.decode();
    window.scrollTo(0, 800);
    link.focus({preventScroll:true});
    const position = window.scrollY, page = document.querySelector('.psalm');
    link.click();
    await wait(() => document.querySelector('#prayer-share-panel:not([hidden]) svg'));
    const panel = document.getElementById('prayer-share-panel');
    require(panel.getAttribute('data-url') === expected, 'Share target changed');
    require(panel.querySelector('image.qr-app-icon'), 'Application icon is missing from QR');
    require(document.querySelector('.psalm') === page, 'Reader content replaced');
    const body = panel.querySelector('.prayer-share-body');
    const toolbar = panel.querySelector('.prayer-share-toolbar');
    require(body.scrollHeight > body.clientHeight, 'Whole panel body must scroll in a short viewport');
    require(toolbar.getBoundingClientRect().top >= 0, 'Toolbar is not visible');
    const color = getComputedStyle(body.querySelector('p')).color;
    require(color === 'rgb(255, 255, 255)', 'Reader palette leaked into panel text: ' + color);
    require(getComputedStyle(panel.querySelector('rect')).fill === 'rgb(255, 255, 255)', 'QR background changed');
    require(getComputedStyle(panel.querySelector('path')).fill === 'rgb(0, 0, 0)', 'QR foreground changed');
    body.scrollTop = body.scrollHeight;
    panel.querySelector('.prayer-share-copy').click();
    await wait(() => panel.querySelector('.prayer-share-status').textContent.length > 0);
    require(copied === expected, 'Clipboard target differs from QR target');
    document.dispatchEvent(new KeyboardEvent('keydown', {key:'Escape', bubbles:true}));
    require(panel.hidden, 'Escape did not close the panel');
    require(window.scrollY === position, 'Closing lost the reading position');
    require(document.activeElement === link, 'Closing lost keyboard focus');
    // A second opening must not retain stale panel handlers or duplicate IDs.
    history.replaceState(history.state, '', location.pathname + location.search + '#rsnk');
    expected = base + '#rsnk';
    link.click();
    await wait(() => document.querySelector('#prayer-share-panel:not([hidden]) svg'));
    require(document.querySelectorAll('#prayer-share-panel').length === 1, 'Duplicate panel after reopening');
    require(document.querySelector('#prayer-share-panel').getAttribute('data-url') === expected,
      'Reopening used a stale anchor');
    document.querySelector('.prayer-share-close').click();
    result.ok = true;
  } catch (error) { result.error = String(error); }
  document.body.insertAdjacentHTML('beforeend', '<pre id="test-result">' + JSON.stringify(result) + '</pre>');
})();
'''

DIRECT_CHECK = r'''
(async function () {
  const result = {};
  try {
    let panel;
    for (let i = 0; i < 500; ++i) {
      panel = document.querySelector('#prayer-share-panel:not([hidden])');
      if (panel && panel.querySelector('svg') && panel.getAttribute('data-url').endsWith(location.hash)) break;
      await new Promise(resolve => setTimeout(resolve, 20));
    }
    if (!panel || !panel.querySelector('svg') || !panel.getAttribute('data-url').endsWith('#rsnk'))
      throw new Error('Direct sharing page did not refresh its QR with the anchor');
    panel.querySelector('.prayer-share-close').click();
    if (!panel.hidden || location.hash !== '#rsnk')
      throw new Error('Closing the direct panel lost the anchor');
    if (new URL(location.href).searchParams.has('share'))
      throw new Error('Closing left the sharing panel request in the address');
    result.ok = true;
  } catch (error) { result.error = String(error); }
  document.body.insertAdjacentHTML('beforeend', '<pre id="test-result">' + JSON.stringify(result) + '</pre>');
})();
'''


QR_SAMPLES = []
for length in (60, 150, 400, 900, 1350, 1800, 1990):
    prefix = 'https://breviar.sk/cgi-bin/l.cgi?qt=pst&st=1&j=sk&sh=1#'
    QR_SAMPLES.append((prefix + 'abcdefghijklmnopqrstuvwxyz0123456789' * 60)[:length])

QR_CHECK = r'''
(async function () {
  const result = {codes: []};
  try {
    const samples = SAMPLES;
    for (const text of samples) {
      const image = new Image();
      await new Promise((resolve, reject) => {
        image.onload = resolve;
        image.onerror = () => reject(new Error('Cannot render branded SVG'));
        image.src = '/qr.svg?text=' + encodeURIComponent(text);
      });
      for (const size of [768, 512, 384]) {
        const canvas = document.createElement('canvas');
        canvas.width = canvas.height = size;
        canvas.getContext('2d').drawImage(image, 0, 0, size, size);
        result.codes.push({text: text, png: canvas.toDataURL('image/png')});
      }
    }
    result.ok = true;
  } catch (error) { result.error = String(error); }
  document.body.insertAdjacentHTML('beforeend', '<pre id="test-result">' + JSON.stringify(result) + '</pre>');
})();
'''.replace('SAMPLES', json.dumps(QR_SAMPLES))


class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        url = urlsplit(self.path)
        if url.path == '/check.js':
            data, kind = CHECK.encode(), 'text/javascript'
        elif url.path == '/direct-check.js':
            data, kind = DIRECT_CHECK.encode(), 'text/javascript'
        elif url.path == '/qr-check.html':
            data, kind = ('<!doctype html><html><body><script>' + QR_CHECK
                          + '</script></body></html>').encode(), 'text/html; charset=utf-8'
        elif url.path == '/qr.svg':
            text = parse_qs(url.query)['text'][0]
            data = subprocess.check_output([str(ENCODER), text], timeout=30)
            kind = 'image/svg+xml'
        elif url.path in ('/test.html', '/direct.html', '/cgi-bin/l.cgi'):
            query = url.query or ('qt=pdt&d=13&m=11&r=2026&p=mv&j=sk&o0=533123'
                                  '&c=1&ct1=123456&cr1=abcdef&c1=334455')
            data = subprocess.check_output([str(CGI)], cwd=ROOT / 'source', timeout=30,
                env=dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=query,
                         HTTP_X_BREVIAR_SHARE_FRAGMENT=self.headers.get('X-Breviar-Share-Fragment', ''))).split(b'\n\n', 1)[1]
            if url.path == '/test.html':
                data = data.replace(b'</body>', b'<script src="/check.js"></script></body>')
            elif url.path == '/direct.html':
                data = data.replace(b'</body>', b'<script src="/direct-check.js"></script></body>')
            kind = 'text/html; charset=utf-8'
        else:
            path = (ROOT / url.path.lstrip('/')).resolve()
            if not path.is_relative_to(ROOT) or not path.is_file():
                self.send_error(404)
                return
            data, kind = path.read_bytes(), mimetypes.guess_type(path)[0] or 'application/octet-stream'
        self.send_response(200)
        self.send_header('Content-Type', kind)
        self.send_header('Content-Length', str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def log_message(self, *args):
        pass


server = ThreadingHTTPServer(('127.0.0.1', 0), Handler)
threading.Thread(target=server.serve_forever, daemon=True).start()
try:
    for path in ('/test.html', '/direct.html?qt=pst&st=1&j=sk&share=1#rsnk', '/qr-check.html'):
        with tempfile.TemporaryDirectory(prefix='breviar-share-browser-') as folder:
            run = subprocess.run([BROWSER, '--headless', '--no-sandbox', '--disable-gpu',
                '--disable-dev-shm-usage', '--disable-background-networking', '--window-size=700,420',
                '--user-data-dir=' + folder, '--virtual-time-budget=15000', '--dump-dom',
                f'http://127.0.0.1:{server.server_port}{path}'], check=True,
                capture_output=True, text=True, timeout=60)
            match = re.search(r'<pre id="test-result">(\{.*?)</pre>', run.stdout)
            assert match, 'Browser did not finish the UI checks'
            result = json.loads(unescape(match[1]))
            assert result.get('ok'), (path, result)
            for code in result.get('codes', []):
                image = Image.open(io.BytesIO(base64.b64decode(code['png'].split(',', 1)[1]))).convert('RGB')
                red, green, blue = image.split()
                assert ImageChops.difference(red, green).getbbox() or ImageChops.difference(green, blue).getbbox(), 'Missing colored app icon'
                decoded = zxingcpp.read_barcode(image)
                assert decoded is not None and decoded.text == code['text'], (
                    'Cannot decode branded QR', len(code['text']), image.size)
finally:
    server.shutdown()
print('Web sharing browser checks passed, including decoding 21 branded SVGs at different link lengths and sizes')
