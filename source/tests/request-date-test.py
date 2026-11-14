#!/usr/bin/env python3
"""Follow real prayer links while moving the renderer's clock across day/year boundaries."""
from datetime import datetime, timezone
from html import unescape
from html.parser import HTMLParser
from pathlib import Path
import re
import subprocess
import sys
import unittest
from urllib.parse import parse_qsl, urlencode, urlsplit

RENDERER = Path(sys.argv.pop(1)).resolve()
ROOT = Path(__file__).resolve().parents[1]


def render(params, clock='2026-11-12T12:00:00'):
    timestamp = int(datetime.fromisoformat(clock).replace(tzinfo=timezone.utc).timestamp())
    return subprocess.check_output([str(RENDERER), str(timestamp), urlencode(params)],
                                   cwd=ROOT, timeout=30).decode()


class Links(HTMLParser):
    def __init__(self, html):
        super().__init__()
        self.urls = []
        self.feed(html)

    def handle_starttag(self, tag, attrs):
        attribute = 'href' if tag == 'a' else 'action' if tag == 'form' else None
        self.urls.extend(value for name, value in attrs if name == attribute)


def query(url):
    return dict(parse_qsl(urlsplit(url).query, keep_blank_values=True))


def psalms(html):
    return re.findall(r'<div class="psalm-name">(.*?)</div>', html)


def resolved(html):
    match = re.search(r'id="breviar-request" hidden data-query="([^"]+)"', html)
    return query('?' + unescape(match[1])) if match else None


class ChristmasYearTest(unittest.TestCase):
    def test_explicit_reference_year_is_independent_of_clock(self):
        for season in (3, 4):
            for year in (2026, 2027):
                with self.subTest(season=season, year=year):
                    params = dict(qt='plo', lo=season, t=1 if season == 3 else 2,
                                  dvt=1, lr='C', j='sk', p='mrch', o2=29432, r=year)
                    first = render(params)
                    second = render(params, '2027-11-12T12:00:00')
                    self.assertTrue(psalms(first))
                    self.assertEqual(psalms(first), psalms(second))
                    self.assertEqual(resolved(first)['r'], str(year))
                    links = [query(url) for url in Links(first).urls
                             if query(url).get('qt') == 'plo']
                    self.assertTrue(links)
                    for link in links:
                        self.assertEqual(link['r'], str(year))
                        self.assertEqual(link['dvt'], '1')
                    # The current-prayer button must round-trip the actual content.
                    same = next(link for link in links if link.get('p') == 'mrch')
                    self.assertEqual(psalms(first), psalms(render(same, '2027-11-12T12:00:00')))

    def test_missing_year_uses_the_backend_year_and_links_freeze_it(self):
        params = dict(qt='plo', lo=3, t=1, dvt=1, lr='C', j='sk', p='mrch', o2=29432)
        for year in (2026, 2027):
            html = render(params, f'{year}-11-12T12:00:00')
            same = next(query(url) for url in Links(html).urls if query(url).get('p') == 'mrch')
            self.assertEqual(same['r'], str(year))
            self.assertEqual(psalms(html), psalms(render(same)))

    def test_reference_year_validation(self):
        for year in ('0', '-1', '10000', '2026bad'):
            html = render(dict(qt='plo', lo=3, t=1, dvt=1, lr='C', p='mrch', r=year))
            self.assertIn('Nevhodné údaje', html)
            self.assertFalse(psalms(html))


class DailyPrayerDateTest(unittest.TestCase):
    def test_saint_and_alternative_links_remain_valid_on_the_next_day(self):
        html = render(dict(qt='pdnes', j='sk', p='mpc', ds=1, o2=29432))
        self.assertTrue(psalms(html))
        self.assertEqual(resolved(html)['qt'], 'pdt')
        self.assertEqual(resolved(html)['d'], '12')
        self.assertEqual(resolved(html)['ds'], '1')
        choices = [query(url) for url in Links(html).urls if urlsplit(url).fragment
                   and query(url).get('p') == 'mpc']
        self.assertTrue(choices)
        for choice in choices:
            with self.subTest(choice=choice):
                self.assertEqual(choice['qt'], 'pdt')
                self.assertEqual(choice['d'], '12')
                before = render(choice)
                after = render(choice, '2026-11-13T12:00:00')
                self.assertTrue(psalms(after))
                self.assertEqual(psalms(before), psalms(after))
        # The resolved URL itself is suitable for sharing without recomputing its date.
        self.assertEqual(psalms(html), psalms(render(resolved(html), '2026-11-13T12:00:00')))

    def test_overview_stays_dynamic_but_its_prayer_buttons_are_dated(self):
        params = dict(qt='pdnes', j='sk', o2=29432)
        first = render(params)
        next_day = render(params, '2026-11-13T12:00:00')
        self.assertIsNone(resolved(first))
        self.assertIsNone(resolved(next_day))
        for html, day in ((first, '12'), (next_day, '13')):
            prayers = [query(url) for url in Links(html).urls
                       if query(url).get('p') in ('mpc', 'mrch', 'mv', 'mk')]
            self.assertTrue(prayers)
            for prayer in prayers:
                self.assertEqual(prayer['qt'], 'pdt')
                self.assertEqual(prayer['d'], day)

    def test_delayed_day_boundary_month_and_year_rollovers(self):
        for clock, date in (
            ('2026-11-13T00:30:00', ('12', '11', '2026')),
            ('2026-11-13T02:30:00', ('13', '11', '2026')),
            ('2027-01-01T00:30:00', ('31', '12', '2026')),
            ('2027-01-01T02:30:00', ('1', '1', '2027')),
            ('2026-12-01T00:30:00', ('30', '11', '2026')),
        ):
            with self.subTest(clock=clock):
                page = resolved(render(dict(qt='pdnes', j='sk', p='mrch'), clock))
                self.assertEqual(tuple(page[k] for k in ('d', 'm', 'r')), date)

    def test_evening_prayers_keep_the_original_date_and_prayer_pair(self):
        for date, prayer in ((8, 'mv'), (8, 'mk'), (9, 'mpv'), (9, 'mpk')):
            with self.subTest(date=date, prayer=prayer):
                clock = f'2025-11-{date:02d}T12:00:00'
                html = render(dict(qt='pdnes', j='sk', p=prayer), clock)
                page = resolved(html)
                self.assertEqual(page['d'], str(date))
                self.assertEqual(page['p'], prayer)
                self.assertTrue(psalms(html))
                self.assertEqual(psalms(html), psalms(render(page, '2026-01-01T12:00:00')))

    def test_browser_adopts_the_resolved_query_without_navigation(self):
        html = render(dict(qt='pdnes', j='sk', p='mpc'))
        script = re.search(r'<script>\s*(\(function \(\).*?)</script>', html, re.S)[1]
        harness = """
const vm = require('vm');
const assert = require('assert');
const script = JSON.parse(process.argv[1]);
let replacement;
const state = {position: 42};
const history = {state, replaceState: (...args) => {replacement = args;}};
const context = {window: {history}, history,
  document: {getElementById: () => ({getAttribute: () => 'qt=pdt&d=12&m=11&r=2026'})},
  location: {pathname: '/cgi-bin/l.cgi', hash: '#ZALM95'}};
vm.runInNewContext(script, context);
assert.strictEqual(replacement[0], state);
assert.strictEqual(replacement[2], '/cgi-bin/l.cgi?qt=pdt&d=12&m=11&r=2026#ZALM95');
context.window.history = null;
vm.runInNewContext(script, context);
"""
        import json
        subprocess.check_call(['node', '-e', harness, json.dumps(script)])


if __name__ == '__main__':
    unittest.main()
