#!/usr/bin/env python3
"""Exercise Commons celebration ranks through the real CGI links and prayers."""
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
PROMOTE = 'OVERRIDE-STUPEN-SLAVENIA'
FEAST_OR_SOLEMNITY = 'STUPEN-SLAVENIA-SVIATOK-SLAVNOST'


def plain_text(html):
    return unescape(re.sub(r'<[^>]*>', '', html))


class Page:
    def __init__(self, parameters):
        # Templates are resolved relative to the CGI working directory.
        self.html = subprocess.check_output(
            [str(CGI)], cwd=ROOT / 'source', timeout=30,
            env=dict(os.environ, REQUEST_METHOD='GET',
                     QUERY_STRING=urlencode(parameters))).decode('utf-8')
        self.ranks = re.findall(r'<span class="redtitle">(.*?)</span>', self.html)
        self.links = {
            urlsplit(unescape(href)).fragment: unescape(href)
            for href in re.findall(r'<a href="([^"]+)"', self.html)
            if urlsplit(unescape(href)).query
        }
        self.psalms = [plain_text(text) for text in
                       re.findall(r'<div class="psalm-name">(.*?)</div>', self.html)]

    def follow(self, fragment):
        return Page(dict(parse_qsl(urlsplit(self.links[fragment]).query)))


def common(**parameters):
    # Wednesday of week 28, with the Common of one male martyr. Enable Te Deum
    # and option links, but not the optional complementary daytime psalmody.
    query = dict(qt='plo', lo=5, t=28, dvt=3, lr='C', j='la', p='mpc',
                 o1=1, o2=512, o3=6)
    query.update(parameters)
    return Page(query)


class CommonCelebrationTest(unittest.TestCase):
    def test_rank_links_round_trip(self):
        for common_part in (6, 7):  # One martyr and several martyrs.
            with self.subTest(common=common_part):
                memorial = common(o3=common_part)
                self.assertEqual(memorial.ranks, ['memoria'])
                feast = memorial.follow(PROMOTE)
                self.assertEqual(feast.ranks, ['memoria – ut festum celebrare'])
                solemnity = feast.follow(FEAST_OR_SOLEMNITY)
                self.assertEqual(solemnity.ranks, ['memoria – ut sollemnitas celebrare'])
                feast_again = solemnity.follow(FEAST_OR_SOLEMNITY)
                self.assertEqual(feast_again.ranks, feast.ranks)
                self.assertEqual(feast_again.psalms, feast.psalms)
                restored = feast_again.follow(PROMOTE)
                self.assertEqual(restored.ranks, memorial.ranks)
                self.assertEqual(restored.psalms, memorial.psalms)

    def test_direct_solemnity_and_return_to_memorial(self):
        memorial = common()
        solemnity = memorial.follow(FEAST_OR_SOLEMNITY)
        self.assertEqual(solemnity.ranks, ['memoria – ut sollemnitas celebrare'])
        restored = solemnity.follow(PROMOTE)
        self.assertEqual(restored.ranks, memorial.ranks)
        self.assertEqual(restored.psalms, memorial.psalms)

    def test_prayers_follow_the_selected_rank(self):
        # Checking the heading alone would miss a regression where Commons
        # with no calendar saint selected stop using the promoted rank.
        for rank, options, first_psalms in (
            ('memoria', 1, ('Psalmus 102 (103)', 'Psalmus 118 (119), 145-152',
                            'Psalmus 30 (31), 2-6')),
            ('memoria – ut festum celebrare', 65537,
             ('Psalmus 2', 'Psalmus 118 (119), 145-152', 'Psalmus 30 (31), 2-6')),
            ('memoria – ut sollemnitas celebrare', 196609,
             ('Psalmus 2', 'Psalmus 122 (123)', 'Psalmus 90 (91)')),
        ):
            for prayer, first_psalm in zip(('mpc', 'mna', 'mk'), first_psalms):
                with self.subTest(rank=rank, prayer=prayer):
                    page = common(p=prayer, o1=options | 4096)  # Show Commons description.
                    self.assertEqual(page.ranks, [rank])
                    self.assertTrue(page.psalms, 'Prayer text is missing')
                    self.assertEqual(page.psalms[0], first_psalm)
                    if options != 1:
                        self.assertIn('<!--spol_cast:begin-->', page.html)
                    if prayer == 'mpc':
                        self.assertEqual('Te Deum laudámus' in page.html, options != 1)

    def test_calendar_feast_still_promotes_to_solemnity(self):
        page = Page(dict(qt='pdt', d=10, m=8, r=2026, ds=1, j='la', p='mpc',
                         o1=1, o2=512))  # St Lawrence, an actual calendar feast.
        self.assertEqual(page.ranks, ['festum'])
        promoted = page.follow(PROMOTE)
        self.assertEqual(promoted.ranks, ['festum – ut sollemnitas celebrare'])
        self.assertNotIn(FEAST_OR_SOLEMNITY, promoted.links)
        self.assertEqual(promoted.follow(PROMOTE).ranks, page.ranks)

    def test_weekday_without_a_common_is_not_promoted(self):
        weekday = common(o3=28)
        for options in (65537, 196609):
            with self.subTest(options=options):
                page = common(o3=28, o1=options)
                self.assertEqual(page.ranks, [])
                self.assertEqual(page.psalms, weekday.psalms)
                self.assertNotIn('Te Deum laudámus', page.html)


class LateranComplineTest(unittest.TestCase):
    def page(self, **parameters):
        query = dict(qt='pdt', d=9, m=11, r=2026, j='sk', p='mk',
                     o0=0, o1=127, o2=512)
        query.update(parameters)
        return Page(query)

    def assert_complete(self, page):
        self.assertEqual(re.findall(r'<!--[^>]*not found[^>]*-->', page.html), [])
        self.assertTrue(page.psalms, 'Prayer text is missing')

    def test_compline_on_every_weekday(self):
        # November 9 skips ordinary psalter initialization. It must still have
        # weekday Compline, or Sunday Compline after first/second Vespers.
        for year, expected in (
            (2026, (['Žalm 86'], ['Žalm 86 (85)'], ['Psalmus 85 (86)'])),
            (2027, (['Žalm 143, 1-11'], ['Žalm 143 (142), 1-11'],
                    ['Psalmus 142 (143), 1-11'])),
            (2022, (['Žalm 31, 2-6', 'Žalm 130'],
                    ['Žalm 31 (30), 2-6', 'Žalm 130 (129)'],
                    ['Psalmus 30 (31), 2-6', 'Psalmus 129 (130)'])),
            (2023, (['Žalm 16'], ['Žalm 16 (15)'], ['Psalmus 15 (16)'])),
            (2029, (['Žalm 88'], ['Žalm 88 (87)'], ['Psalmus 87 (88)'])),
            (2024, (['Žalm 4', 'Žalm 134'], ['Žalm 4', 'Žalm 134 (133)'],
                    ['Psalmus 4', 'Psalmus 133 (134)'])),
            (2025, (['Žalm 91'], ['Žalm 91 (90)'], ['Psalmus 90 (91)'])),
        ):
            for language, psalms in zip(('sk', 'cz', 'la'), expected):
                # Both the day's default Compline and the feast's own link.
                for selection in ({}, dict(ds=1)):
                    with self.subTest(year=year, language=language, **selection):
                        page = self.page(r=year, j=language, **selection)
                        self.assertEqual(page.psalms, psalms)
                        self.assert_complete(page)

    def test_first_vespers_and_compline_on_eve_of_sunday_feast(self):
        for evening_prayer, first_prayer, psalms in (
            ('mv', 'mpv', ['Žalm 147, 1-11', 'Žalm 147, 12-20', 'Chválospev']),
            ('mk', 'mpk', ['Žalm 4', 'Žalm 134']),
        ):
            for day, prayer in ((8, evening_prayer), (9, first_prayer)):
                with self.subTest(day=day, prayer=prayer):
                    page = self.page(r=2025, d=day, p=prayer)
                    self.assertEqual(page.psalms, psalms)
                    self.assertIn('výročie posviacky lateránskej baziliky',
                                  plain_text(page.html).casefold())
                    if evening_prayer == 'mk':
                        self.assert_complete(page)

    def test_promotion_to_solemnity_keeps_sunday_compline(self):
        for language, psalm in (('sk', 'Žalm 91'), ('cz', 'Žalm 91 (90)'),
                                ('la', 'Psalmus 90 (91)')):
            with self.subTest(language=language):
                page = self.page(j=language, ds=1).follow(PROMOTE)
                self.assertEqual(page.psalms, [psalm])
                self.assert_complete(page)


if __name__ == '__main__':
    unittest.main()
