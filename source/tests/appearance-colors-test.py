#!/usr/bin/env python3
"""Color overrides survive real renderer requests and preserve CSS defaults."""
from html.parser import HTMLParser
import os
from pathlib import Path
import subprocess
import sys
import unittest
from urllib.parse import parse_qsl, urlencode, urlsplit

ROOT = Path(__file__).resolve().parents[2]
CGI = Path(sys.argv.pop(1)).resolve() if len(sys.argv) > 1 else ROOT / 'l.cgi'


def render(**parameters):
    query = dict(qt='pst', st='2', p='mrch', j='sk')
    query.update(parameters)
    return subprocess.check_output([str(CGI)], cwd=ROOT / 'source', timeout=30,
        env=dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=urlencode(query))).decode()


class Page(HTMLParser):
    def __init__(self, html):
        super().__init__()
        self.root_style = ''
        self.links = []
        self.feed(html)

    def handle_starttag(self, tag, attrs):
        attrs = dict(attrs)
        if tag == 'html':
            self.root_style = attrs.get('style', '')
        if tag == 'a' and 'href' in attrs:
            self.links.append(attrs['href'])


class AppearanceColorsTest(unittest.TestCase):
    def test_defaults_do_not_emit_overrides(self):
        for theme in (0, 1):
            self.assertEqual(Page(render(c=theme)).root_style, '')

    def test_only_active_palette_is_applied_and_both_are_preserved_in_links(self):
        palettes = dict(ct0='123456', cr0='abcdef', c0='ffffcc',
                        ct1='ffffff', cr1='ffff00', c1='000000')
        for theme in (0, 1):
            page = Page(render(c=theme, **palettes))
            for role, key in [('text', 'ct'), ('rubric', 'cr'), ('background', 'c')]:
                self.assertIn('--prayer-' + role + ': #' + palettes[key + str(theme)], page.root_style)
            links = [dict(parse_qsl(urlsplit(link).query)) for link in page.links
                     if urlsplit(link).path == '/cgi-bin/l.cgi']
            self.assertTrue(links)
            for link in links:
                for key, value in palettes.items():
                    self.assertEqual(link.get(key), value, key)

    def test_shorthand_invalid_input_and_explicit_reset(self):
        self.assertIn('--prayer-text: #aabbcc', Page(render(ct0='AbC')).root_style)
        for value in ('', 'gggggg', 'ffffff; color: red', '#ffffff'):
            self.assertNotIn('--prayer-text', Page(render(ct0=value)).root_style)
        page = Page(render(c0='def', c1='abc', ct0=''))
        self.assertIn('background-color: #ddeeff', page.root_style)
        self.assertNotIn('--prayer-text', page.root_style)

    def test_information_dialogs_use_the_same_palette(self):
        for page in ('about', 'changelog', 'tts-help'):
            style = Page(render(st='text', p=page, c=1, ct1='eeeeee', cr1='ffaaaa', c1='111111')).root_style
            self.assertIn('--prayer-text: #eeeeee', style)
            self.assertIn('--prayer-rubric: #ffaaaa', style)
            self.assertIn('--prayer-background: #111111', style)

    def test_saved_colors_and_explicit_resets_override_a_stale_reader_url(self):
        query = ('qt=pst&st=2&p=mrch&j=sk&c=0&ct0=&cr0=abcdef&c0=ffffcc'
                 '&ct0=ffffff&cr0=111111&c0=000000')
        html = subprocess.check_output([str(CGI)], cwd=ROOT / 'source', timeout=30,
            env=dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=query)).decode()
        style = Page(html).root_style
        self.assertNotIn('--prayer-text', style)
        self.assertIn('--prayer-rubric: #abcdef', style)
        self.assertIn('--prayer-background: #ffffcc', style)


if __name__ == '__main__':
    unittest.main()
