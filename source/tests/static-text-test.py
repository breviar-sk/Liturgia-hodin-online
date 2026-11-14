#!/usr/bin/env python3
"""Exercise the public static-text URLs and follow generated content links."""
from html import unescape
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
    def test_readings_and_compline_keep_the_opening_doxology(self):
        for language, first_words in (('sk', 'Sláva Otcu'), ('la', 'Glória Patri'),
                                      ('is', 'Dýrð sé Föðurnum')):
            for prayer in ('mpc', 'mk'):
                with self.subTest(language=language, prayer=prayer):
                    html = body(render(j=language, p=prayer))
                    self.assertRegex(html, r'</div>\s*<p class="par">' + re.escape(first_words))

    def test_hungarian_salve_regina_retains_the_stanza_in_the_static_edition(self):
        text = ' '.join(unescape(re.sub('<[^>]*>', ' ', body(render(j='hu', st='1')))).split())
        self.assertIn('hol vagy örök dicsőségben. Áldott légy, drágalátos Szűz! '
                      'Isten véled, szép virág, Szűz! Mennyben szent Fiad mellett ülsz, '
                      's tudjuk, rajtunk is könyörülsz. Azért Szószólónk, szemedet,', text)

    def test_czech_supplemental_links_match_their_labels(self):
        html = render(j='cz', p='mi')
        match = re.search(r'<a href="([^"]+)">\s*95 \(94\)</a>', html)
        self.assertIsNotNone(match)
        self.assertEqual('psalm-95', dict(parse_qsl(urlsplit(unescape(match[1])).query))['p'])
        html = render(j='cz', p='mv')
        match = re.search(r'kratšími prosbami.*?<a href="([^"]+)">', html, re.S)
        self.assertIsNotNone(match)
        self.assertEqual('intercessions', dict(parse_qsl(urlsplit(unescape(match[1])).query))['p'])

    def test_ordinarium_documents_link_to_each_other_inside_the_exported_section(self):
        for language in LANGUAGES:
            for st, prayer in [('2', p) for p in OFFICES] + [('1', '')]:
                with self.subTest(language=language, prayer=prayer, st=st):
                    html = render(j=language, st=st, p=prayer, o0=1,
                                  c=1, c1='123456', ff=24)
                    bars = re.findall(r'<p class="center ordinarium-navigation">(.*?)</p>', html, re.S)
                    self.assertEqual(1, len(bars))
                    links = [dict(parse_qsl(urlsplit(url).query)) for url in Links(bars[0]).urls]
                    self.assertEqual(['mi', 'mrch', 'mpc', 'mna', 'mv', 'mk'], [p['p'] for p in links if p['st'] == '2'])
                    self.assertEqual(1, sum(p['st'] == '1' for p in links))
                    for p in links:
                        self.assertEqual(language, p['j'])
                        self.assertEqual('1', p['c'])
                        self.assertEqual('123456', p['c1'])
                        self.assertEqual('24', p['ff'])
                    self.assertNotIn('ordinarium-navigation', render(j=language, st=st, p=prayer, o0=256))

    def test_web_menus_offer_the_same_six_ordinarium_offices_as_the_app(self):
        expected = ['mi', 'mrch', 'mpc', 'mna', 'mv', 'mk']
        for language in LANGUAGES:
            for query in (('pdnes', 'pst') if language in ('sk', 'cz', 'c2', 'hu', 'la', 'is') else ('pst',)):
                with self.subTest(language=language, query=query):
                    html = render(qt=query, j=language, p='mrch', o0=524288,
                                  c=1, c1='123456', ff=24)
                    menus = re.findall(r'<div class="dropdown-container ordinarium-menu">(.*?)</div>', html, re.S)
                    self.assertEqual(2, len(menus))  # left and right drawers
                    for menu in menus:
                        params = [dict(parse_qsl(urlsplit(url).query)) for url in Links(menu).urls]
                        self.assertEqual(expected, [p['p'] for p in params])
                        for p in params:
                            self.assertEqual('pst', p['qt'])
                            self.assertEqual('2', p['st'])
                            self.assertEqual(language, p['j'])
                            # Web drawers keep day/night mode in sessionStorage.
                            self.assertNotIn('c', p)
                            self.assertEqual('123456', p['c1'])
                            self.assertEqual('24', p['ff'])
        for filename, language in (('sidemenu.htm', 'sk'), ('sidemenu_cz.htm', 'cz'),
                ('sidemenu_czop.htm', 'c2'), ('sidemenu_hu.htm', 'hu'),
                ('sidemenu_la.htm', 'la'), ('sidemenu_is.htm', 'is'), ('sidemenu_es.htm', 'es')):
            with self.subTest(filename=filename):
                menus = re.findall(r'<div class="dropdown-container ordinarium-menu">(.*?)</div>',
                                   (ROOT / filename).read_text(), re.S)
                self.assertEqual(2, len(menus))
                for menu in menus:
                    params = [dict(parse_qsl(urlsplit(url).query)) for url in Links(menu).urls]
                    self.assertEqual(expected, [p['p'] for p in params])
                    self.assertTrue(all(p['qt'] == 'pst' and p['st'] == '2' and p['j'] == language for p in params))

    def test_all_main_offices_render_text_or_a_localized_placeholder(self):
        for language in LANGUAGES:
            for prayer in OFFICES:
                with self.subTest(language=language, prayer=prayer):
                    html = render(j=language, p=prayer)
                    self.assertNotIn('not found', html)
                    self.assertNotIn('Neznámy typ modlitby', html)
                    self.assertNotIn('{link:', html)
                    self.assertGreater(len(re.sub('<[^>]*>', '', body(html)).strip()), 30)
        for language, phrase in {'hu': 'még nem érhető el', 'en': 'not yet available',
                'es': 'todavía no está disponible', 'az': 'hələ Azərbaycan'}.items():
            self.assertIn(phrase, render(j=language, p='mpred'))

    def test_czech_daytime_prayer_is_complete_and_shared_by_all_three_hours(self):
        html = render(j='cz', p='mna')
        text = unescape(re.sub('<[^>]*>', '', body(html))).replace('\u00a0', ' ')
        self.assertNotIn('zatím není dostupný', text)
        for passage in ('Dobrý Pane Ježíši', 'marné vše mé snažení',
                        'V tento nyní polední čas', 'Ježíše, našeho Pána',
                        'Miluj Pána Boha svého', 'došel království věčného',
                        'Skrze Krista, našeho Pána', 'Dobrořečme Pánu'):
            self.assertIn(passage, text)
        for prayer in ('mpred', 'mpo'):
            self.assertEqual(body(html), body(render(j='cz', p=prayer)))

    def test_czech_readings_ordinarium_uses_the_existing_czech_static_text(self):
        html = render(j='cz', p='mpc')
        text = unescape(re.sub('<[^>]*>', '', body(html))).replace('\u00a0', ' ')
        self.assertNotIn('zatím není dostupný', text)
        for phrase in ('Bože, pospěš mi na pomoc', 'Čtení jsou dvě',
                       'oslavuje celá země', 'ať nejsme zahanbeni na věky',
                       'Dobrořečme Pánu'):
            self.assertIn(phrase, text)
        self.assertNotIn('Bože, shlédni a pomoz', text)

    def test_dominican_offices_keep_their_independent_translation(self):
        passages = {
            'mi': ('A začnu tě chválit', 'Kéž dnes nasloucháte hlasu Páně',
                   'Pojďme a jásejme vstříc Pánu', 'On, král věčné slávy'),
            'mpc': ('Čtení jsou dvě', 'Bože, tebe chválíme', 'nebudu zahanben na věky'),
            'mrch': ('Požehnaný buď Pán, Bůh Izraele', 'A ty, synu, budeš prorokem'),
            'mna': ('Modlitba během dne', 'Doplňkový cyklus', 'Dobrořečme Pánu'),
            'mv': ('Velebí má duše Pána', 'Prokázal sílu svým ramenem'),
            'mk': ('Ochraňuj nás, Pane, když bdíme', 'Pokojnou noc a šťastnou smrt'),
        }
        for prayer, expected in passages.items():
            with self.subTest(prayer=prayer):
                html = render(j='c2', p=prayer)
                text = unescape(re.sub('<[^>]*>', '', body(html))).replace('\u00a0', ' ')
                self.assertNotIn('zatím není dostupný', text)
                for passage in expected:
                    self.assertIn(passage, text)
                if prayer != 'mi':
                    self.assertIn('Bože, shlédni a pomoz', text)
                    self.assertNotIn('Bože, pospěš mi na pomoc', text)
        self.assertNotIn('Dobrý Pane Ježíši', render(j='c2', p='mna'))
        self.assertNotIn('Pochválen buď Hospodin', render(j='c2', p='mrch'))

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
        for language in ('sk', 'cz', 'c2', 'hu', 'la', 'is'):
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
