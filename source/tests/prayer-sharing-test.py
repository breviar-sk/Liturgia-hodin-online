#!/usr/bin/env python3
"""Follow real sharing actions, including POST settings and relative dates."""
from html.parser import HTMLParser
from pathlib import Path
import os
import base64
import re
import subprocess
import sys
import unittest
from urllib.parse import parse_qsl, quote, unquote, urlencode, urlsplit
import xml.etree.ElementTree as ET

CGI = Path(sys.argv.pop(1)).resolve()
ROOT = Path(__file__).resolve().parents[2]


def render(params, post=False, fragment=None):
    data = urlencode(params)
    env = dict(os.environ, REQUEST_METHOD='POST' if post else 'GET',
               QUERY_STRING='' if post else data, CONTENT_LENGTH=str(len(data)),
               CONTENT_TYPE='application/x-www-form-urlencoded')
    if fragment is not None:
        env['HTTP_X_BREVIAR_SHARE_FRAGMENT'] = fragment
    return subprocess.check_output([str(CGI)], cwd=ROOT / 'source', env=env,
                                   input=data.encode() if post else b'', timeout=30).decode()


class Panel(HTMLParser):
    def __init__(self, html):
        super().__init__()
        self.attrs = None
        self.actions = []
        self.feed(html)

    def handle_starttag(self, tag, attrs):
        attrs = dict(attrs)
        if attrs.get('id') == 'prayer-share-panel':
            self.attrs = attrs
        if attrs.get('class') == 'prayer-share-action':
            self.actions.append(attrs['href'])


class SharingTest(unittest.TestCase):
    def test_normal_pages_defer_qr_work_and_today_remains_dynamic(self):
        html = render(dict(qt='pdnes', j='sk', o0=8835 | 524288))
        panel = Panel(html)
        self.assertIsNotNone(panel.attrs)
        self.assertIn('hidden', panel.attrs)
        self.assertNotIn('<svg', html)
        self.assertTrue(panel.actions)
        url = panel.attrs['data-url']
        self.assertTrue(url.startswith('https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&j=sk&'))
        query = dict(parse_qsl(urlsplit(url).query, keep_blank_values=True))
        self.assertFalse(set(('d', 'm', 'r', 'share', 'dl')) & query.keys())
        self.assertEqual('1', query['sh'])
        self.assertTrue(all(f'o{i}' in query for i in range(7)))
        shared = render(dict(parse_qsl(urlsplit(panel.attrs['data-action']).query)))
        self.assertNotIn('hidden', Panel(shared).attrs)
        self.assertIn('<svg', shared)
        self.assertEqual(url, Panel(shared).attrs['data-url'])
        svg = ET.fromstring(re.search(r'<svg\b.*?</svg>', shared, re.S).group())
        icon = svg.find('{http://www.w3.org/2000/svg}image')
        self.assertIsNotNone(icon)
        self.assertEqual((ROOT / 'android/appicon.png').read_bytes(),
                         base64.b64decode(icon.attrib['href'].split(',', 1)[1]))

    def test_get_and_post_preserve_selection_and_resolved_appearance(self):
        params = dict(qt='pdt', d=12, m=11, r=2026, p='mv', j='cz', c=1,
                      ct0='123456', cr1='abcdef', ff=19, mm=11, o1=7, share=1)
        for post in (False, True):
            with self.subTest(post=post):
                html = render(params, post)
                attrs = Panel(html).attrs
                self.assertIsNotNone(attrs)
                url = attrs['data-url']
                self.assertTrue(url.startswith('https://breviar.sk/cgi-bin/l.cgi?qt=pdt&d=12&m=11&r=2026&p=mv&j=cz&k=&'), url)
                query = dict(parse_qsl(urlsplit(url).query, keep_blank_values=True))
                for key in ('p', 'j', 'c', 'ct0', 'cr1', 'ff', 'mm', 'o1'):
                    self.assertEqual(str(params[key]), query[key])
                self.assertNotIn('share', query)
                self.assertEqual('1', query['sh'])
                self.assertIn('<svg', html)
                # A complete share link renders the same selected psalms.
                again = render(query)
                self.assertEqual(re.findall('<div class="psalm-name">(.*?)</div>', html),
                                 re.findall('<div class="psalm-name">(.*?)</div>', again))

    def test_ordinary_language_and_christmas_reference_year_are_preserved(self):
        for params, expected in (
                (dict(qt='pst', st=2, p='mna', j='c2'), dict(qt='pst', st='2', p='mna', j='c2')),
                (dict(qt='plo', lo=3, t=1, dvt=1, lr='C', p='mrch', r=2027), dict(qt='plo', r='2027', lo='3'))):
            params['share'] = 1
            html = render(params)
            panel = Panel(html)
            self.assertIn('<svg', html)
            actual = dict(parse_qsl(urlsplit(panel.attrs['data-url']).query))
            for key, value in expected.items():
                self.assertEqual(value, actual[key])
        self.assertIsNone(Panel(render(dict(qt='pst', st=3))).attrs)
        self.assertIsNone(Panel(render(dict(qt='pxml', d=13, m=11, r=2026))).attrs)

    def test_marian_antiphons_share_and_reopen_the_same_document(self):
        for selector in (1, 'ma'):
            with self.subTest(selector=selector):
                html = render(dict(qt='pst', st=selector, j='sk', share=1, o0=8835 | 524288))
                panel = Panel(html)
                self.assertTrue(panel.actions)
                self.assertIn('<svg', html)
                query = dict(parse_qsl(urlsplit(panel.attrs['data-url']).query))
                self.assertEqual('pst', query['qt'])
                self.assertEqual('1', query['st'])
                self.assertNotIn('p', query)
                again = render(query)
                self.assertIn('MARIÁNSKE ANTIFÓNY', again)
                self.assertIn('Slávna Matka Spasiteľa', again)
                self.assertEqual(panel.attrs['data-url'], Panel(again).attrs['data-url'])

    def test_fragment_header_is_encoded_once_without_changing_prayer_parameters(self):
        for post, params in (
                (False, dict(qt='pst', st=1, j='sk', share=1)),
                (True, dict(qt='pdt', d=12, m=11, r=2026, p='mv', j='sk', share=1))):
            plain = Panel(render(params, post=post)).attrs['data-url']
            for fragment in ('rsnk', 'Zdravas’, Mária + 20%', 'a%20b', 'a&b#c?d'):
                encoded = quote(fragment, safe='')
                with self.subTest(fragment=fragment, post=post):
                    html = render(params, post=post, fragment=encoded)
                    panel = Panel(html)
                    self.assertEqual(plain + '#' + encoded, panel.attrs['data-url'])
                    self.assertEqual(fragment, unquote(urlsplit(panel.attrs['data-url']).fragment))
                    self.assertEqual('', urlsplit(panel.attrs['data-action']).fragment)
                    self.assertIn('<svg', html)
        params = dict(qt='pst', st=1, j='sk')
        # This is QR metadata only, not a persistent prayer option.
        self.assertEqual(Panel(render(params)).attrs['data-url'],
                         Panel(render(params, fragment='rsnk')).attrs['data-url'])


if __name__ == '__main__':
    unittest.main()
