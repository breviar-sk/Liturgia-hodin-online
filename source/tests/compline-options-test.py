#!/usr/bin/env python3
"""Compline's penitential act is independent of rubrics and keeps its alternatives."""
from html import unescape
import os
from pathlib import Path
import re
import subprocess
import sys
import unittest
from urllib.parse import parse_qsl, urlencode, urlsplit

ROOT = Path(__file__).resolve().parents[2]
CGI = Path(sys.argv.pop(1)).resolve() if len(sys.argv) > 1 else ROOT / 'l.cgi'
PENITENTIAL_ACT = 1048576
CONFESSION = {
    'sk': 'Vyznávam všemohúcemu Bohu',
    'cz': 'Vyznávám se všemohoucímu Bohu',
    'c2': 'Vyznávám se všemohoucímu Bohu',
    'is': 'Ég játa fyrir almáttugum Guði',
    'es': 'Yo confieso ante Dios todopoderoso',
    'az': 'Hər şeyə qadir Allaha',
}


def render(**parameters):
    query = dict(qt='pdt', d=10, m=11, r=2026, j='sk', p='mk',
                 o0=0, o1=0, o2=512 | 16384, o6=0)
    query.update(parameters)
    return subprocess.check_output(
        [str(CGI)], cwd=ROOT / 'source', timeout=30,
        env=dict(os.environ, REQUEST_METHOD='GET',
                 QUERY_STRING=urlencode(query))).decode('utf-8')


def follow(html, fragment):
    links = [unescape(href) for href in re.findall(r'<a href="([^"]+)"', html)]
    link = next(href for href in links if urlsplit(href).fragment == fragment)
    return render(**dict(parse_qsl(urlsplit(link).query)))


class ComplineOptionsTest(unittest.TestCase):
    def test_penitential_act_is_independent_of_rubrics_including_tts(self):
        for language, confession in CONFESSION.items():
            for day, prayer in ((10, 'mk'), (15, 'mpk')):
                for voice in (0, 256):
                    for rubrics in (0, 2):
                        for enabled in (False, True):
                            with self.subTest(language=language, prayer=prayer,
                                              voice=voice, rubrics=rubrics, enabled=enabled):
                                html = render(j=language, d=day, p=prayer, o0=voice,
                                              o1=rubrics | (PENITENTIAL_ACT if enabled else 0))
                                self.assertEqual(confession in html, enabled)
                                if not enabled:
                                    self.assertFalse(re.search(r'href="[^"]*#ALT-UKONKAJ-MULTI"', html))
                                self.assertIn('class="psalm-name"', html)
                                self.assertNotIn('{UKONKAJ', html)

    def test_inline_toggle_round_trip_preserves_rubrics(self):
        for rubrics in (0, 2):
            with self.subTest(rubrics=rubrics):
                hidden = render(o1=rubrics)
                shown = follow(hidden, 'ZOBRAZ-UKONKAJ')
                self.assertIn(CONFESSION['sk'], shown)
                hidden_again = follow(shown, 'ZOBRAZ-UKONKAJ')
                self.assertNotIn(CONFESSION['sk'], hidden_again)
                self.assertIn('o1=' + str(rubrics) + '&amp;', shown)
                alternative = follow(shown, 'ALT-UKONKAJ-MULTI')
                self.assertNotIn(CONFESSION['sk'], alternative)
                self.assertIn('Zmiluj sa nad nami, Pane.', alternative)

    def test_force_parameter_overrides_the_word(self):
        for enabled in (0, 1):
            with self.subTest(enabled=enabled):
                html = render(o1=(1 - enabled) * PENITENTIAL_ACT, of1uk=enabled)
                self.assertEqual(CONFESSION['sk'] in html, bool(enabled))


if __name__ == '__main__':
    unittest.main()
