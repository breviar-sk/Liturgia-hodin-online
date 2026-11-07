#!/usr/bin/env python3
"""Check Bible links in the shipped canticle and invitatory templates."""
from html import unescape
import os
from pathlib import Path
import re
import subprocess
import sys
import unittest
from urllib.parse import urlencode

ROOT = Path(__file__).resolve().parents[2]
CGI = Path(sys.argv.pop(1)).resolve() if len(sys.argv) > 1 else ROOT / 'l.cgi'
LANGUAGES = ('sk', 'cz', 'czop', 'hu', 'la', 'is', 'es', 'az')


def render(language, prayer, links):
    query = urlencode(dict(qt='pdt', j=language, d=5, m=11, r=2026,
                           p=prayer, o0=2 if links else 0, o1=127))
    return subprocess.check_output(
        [str(CGI)], cwd=ROOT / 'source', timeout=30,
        env=dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=query)
    ).decode('utf-8')


def captions(html):
    return re.findall(r'<(?:p|div) class="(?:bibleref|psalm-name)">(.*?)</(?:p|div)>',
                      html, re.DOTALL)


def text(html):
    return unescape(re.sub(r'<[^>]*>', '', html))


class PrayerReferencesTest(unittest.TestCase):
    def test_reference_markers_are_balanced(self):
        for folder in sorted(ROOT.glob('include*')):
            for path in sorted(folder.glob('*.htm')):
                content = path.read_text(encoding='utf-8')
                if path.name.startswith('kat-') or not (
                        '{BEGIN:' in content or path.name.startswith('m_')):
                    continue  # Standalone pages do not pass through the renderer.
                with self.subTest(file=str(path.relative_to(ROOT))):
                    opened = False
                    for marker in re.finditer(r'\{r(?::[^}]*)?\}|\{/r\}', content):
                        closing = marker[0] == '{/r}'
                        line = content.count('\n', 0, marker.start()) + 1
                        self.assertEqual(opened, closing,
                                         f'Unpaired reference on line {line}')
                        opened = not closing
                    self.assertFalse(opened, 'Unclosed Bible reference')
                    for link in re.finditer(r'\{(?:k:[^}]*|z95)\}(.*?)\{/(?:k|z95)\}',
                                            content, re.DOTALL):
                        self.assertNotIn('{r', link[1], 'Nested Bible link inside another link')

    def test_canticles_and_invitatory_in_every_language(self):
        for language in LANGUAGES:
            for prayer, citation in (('mv', '1,46-55'), ('mrch', '1,68-79'),
                                     ('mk', '2,29-32'), ('mi', None)):
                with self.subTest(language=language, prayer=prayer):
                    linked = captions(render(language, prayer, True))
                    plain = captions(render(language, prayer, False))
                    self.assertTrue(linked, 'Prayer captions were not rendered')
                    self.assertEqual(list(map(text, linked)), list(map(text, plain)))
                    self.assertTrue(all('<a ' not in caption for caption in plain))
                    if citation:
                        # Local book names and spacing remain unchanged.
                        matches = [caption for caption in linked
                                   if re.sub(r'\s', '', text(caption)).endswith(citation)]
                    else:
                        # Psalm numbering differs between the language editions.
                        matches = [caption for caption in linked
                                   if re.search(r'\b95\b', text(caption))]
                    self.assertTrue(matches, 'Expected canticle/psalm citation is missing')
                    for caption in matches:
                        self.assertIn('<a href="', caption)
                        self.assertNotIn('{r', caption)
                        self.assertNotIn('{/r}', caption)


if __name__ == '__main__':
    unittest.main()
