#!/usr/bin/env python3
"""Exercise the public static-text URLs and follow generated content links."""
from html.parser import HTMLParser
import os
from pathlib import Path
import re
import subprocess
import sys
import unittest
from urllib.parse import parse_qsl, urlencode, urlsplit

ROOT = Path(__file__).resolve().parents[2]
CGI = Path(sys.argv.pop(1)).resolve() if len(sys.argv) > 1 else ROOT / 'l.cgi'
LANGUAGES = ('sk', 'cz', 'c2', 'hu', 'la', 'is', 'en', 'es', 'az')
OFFICES = ('mi', 'mpc', 'mrch', 'mpred', 'mna', 'mpo', 'mv', 'mk')


def render(**params):
    query = dict(qt='pst', st='2', j='sk')
    query.update(params)
    return subprocess.check_output([str(CGI)], cwd=ROOT / 'source', timeout=30,
        env=dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=urlencode(query))).decode()


class Links(HTMLParser):
    def __init__(self, html):
        super().__init__()
        self.urls = []
        self.feed(html)

    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            self.urls.extend(value for name, value in attrs if name == 'href')


def body(html):
    html = re.sub(r'<!--.*?-->', '', html, flags=re.S)
    return re.search(r'<body[^>]*>(.*)</body>', html, re.S).group(1)


class StaticTextTest(unittest.TestCase):
    def test_all_main_offices_render_text_or_a_localized_placeholder(self):
        for language in LANGUAGES:
            for prayer in OFFICES:
                with self.subTest(language=language, prayer=prayer):
                    html = render(j=language, p=prayer)
                    self.assertNotIn('not found', html)
                    self.assertNotIn('Neznámy typ modlitby', html)
                    self.assertNotIn('{link:', html)
                    self.assertGreater(len(re.sub('<[^>]*>', '', body(html)).strip()), 30)
        for language, phrase in {'cz': 'zatím není dostupný', 'c2': 'zatím není dostupný',
                'hu': 'még nem érhető el', 'en': 'not yet available',
                'es': 'todavía no está disponible', 'az': 'hələ Azərbaycan'}.items():
            self.assertIn(phrase, render(j=language, p='mpred'))

    def test_ordinary_selection_uses_only_the_main_offices(self):
        expected = render(p='mrch')
        for prayer in ('', '8', '9', '10', '11', '12', '13', '14', '99', 'unknown', 'mpv', 'mpk'):
            with self.subTest(prayer=prayer):
                self.assertEqual(expected, render(p=prayer))

    def test_numeric_and_symbolic_selectors_and_marian_antiphons(self):
        for language in LANGUAGES:
            for number, name in (('1', 'ma'), ('2', 'ord')):
                self.assertEqual(render(st=number, j=language), render(st=name, j=language))
                self.assertNotIn('not found', render(st=number, j=language))

    def test_generated_links_keep_language_appearance_and_render_their_targets(self):
        count = 0
        for language in ('sk', 'cz', 'hu', 'la', 'is'):
            for prayer in OFFICES:
                html = render(j=language, p=prayer, c=1, c1='123456', ff=24, o0=1)
                for url in Links(html).urls:
                    self.assertNotIn('\u00a0', url)
                    self.assertNotIn('\u202f', url)
                    self.assertNotIn('../include', url)
                    self.assertNotIn('ord_km.htm', url)
                    if '?' not in url or urlsplit(url).scheme:
                        continue
                    parts = urlsplit(url)
                    if parts.path != '/cgi-bin/l.cgi':
                        continue
                    params = dict(parse_qsl(parts.query))
                    if params.get('qt') != 'pst':
                        continue
                    count += 1
                    self.assertEqual(language, params['j'])
                    self.assertEqual('1', params['c'])
                    self.assertEqual('123456', params['c1'])
                    self.assertEqual('24', params['ff'])
                    target = render(**params)
                    self.assertNotIn('not found', target)
                    self.assertIn('breviar-invert-colors.css', target)
                    self.assertIn('#123456', target)
                    self.assertNotRegex(body(target), r'\{/?(?:link|r|v)[:}]')
                    self.assertNotIn('\n class="quiet">', body(target))
                    self.assertGreater(len(re.sub('<[^>]*>', '', body(target)).strip()), 30)
                    if parts.fragment:
                        self.assertRegex(target, r'(?i)(?:name|id)=["\']' + re.escape(parts.fragment) + r'["\']')
        self.assertGreater(count, 30)

    def test_missing_supplemental_translations_render_a_placeholder(self):
        for language in LANGUAGES:
            for page in ('psalm-95', 'psalm-100', 'psalm-67', 'psalm-24',
                         'lord-prayer', 'intercessions', 'penitential-act', 'extended-vigil', 'guidelines'):
                with self.subTest(language=language, page=page):
                    html = render(st='text', p=page, j=language)
                    self.assertNotIn('not found', html)
                    self.assertGreater(len(re.sub('<[^>]*>', '', body(html)).strip()), 30)

    def test_ordinarium_tts_sections_in_every_language(self):
        for path in ROOT.glob('include*/ord_*.htm'):
            source = path.read_text()
            self.assertIn('{TTS:SECTION}', source, str(path))
            self.assertEqual(source.count('{TTS:HEADING_BEGIN}'), source.count('{TTS:HEADING_END}'), str(path))
        for language in LANGUAGES:
            for st, prayers in (('1', ('',)), ('2', OFFICES)):
                for prayer in prayers:
                    with self.subTest(language=language, st=st, prayer=prayer):
                        for voice in (0, 256):
                            html = render(st=st, p=prayer, j=language, o0=voice)
                            self.assertNotIn('{TTS:', html)
                            self.assertGreater(body(html).count('class="tts-section"'), 0)
                            # Include boundaries add navigation without creating pause-only sections.
                            self.assertNotRegex(html, r'<span class="tts-pause"></span>\s*<div class="tts-section">')

    def test_static_sections_are_allowlisted(self):
        for target in ('../../cgi-bin/breviar-web.cfg', '/etc/passwd', 'z95.htm'):
            html = render(st='text', p=target)
            self.assertNotIn('(file `', html)
            self.assertIn('Neznámy typ modlitby', html)


if __name__ == '__main__':
    unittest.main()
