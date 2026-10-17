#!/usr/bin/env python3
"""Self-contained Menu v1 contract checks against real CGI output."""
import os
from pathlib import Path
import subprocess
import sys
import unittest
from urllib.parse import urlencode
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[2]
CGI = Path(sys.argv.pop(1)).resolve() if len(sys.argv) > 1 else ROOT / 'l.cgi'


def export(language='sk', **parameters):
    query = dict(qt='pxml', d='13', m='10', r='2026', j=language)
    query.update(parameters)
    output = subprocess.check_output(
        [str(CGI)], cwd=ROOT, timeout=30,
        env=dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=urlencode(query)))
    return ET.fromstring(output[output.index(b'<?xml'):])


def by_key(element):
    return {node.attrib['Key']: node for node in element.iter() if 'Key' in node.attrib}


class SettingsXmlTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        initial = export()
        languages = [node.attrib['Value'] for node in initial.find('SupportedLanguages')]
        # English labels exercise XML metacharacters even when English is not
        # enabled as a selectable prayer language in this build.
        cls.exports = {language: export(language) for language in set(languages + ['en'])}

    def test_structure_bindings_and_order(self):
        seen = {}
        controls = {'toggle', 'choice', 'color', 'number', 'font', 'action'}
        item_attributes = {'Key', 'Label', 'Control', 'Parameter', 'OptionRef',
                           'ValuesRef', 'ValueAttribute', 'Handler', 'Default',
                           'ResetValue', 'Min', 'Max'}
        for language, root in self.exports.items():
            with self.subTest(language=language):
                menu = root.find('Menu')
                self.assertEqual(menu.attrib, {'Version': '1'})
                actual = by_key(menu)
                self.assertEqual(len(actual), len(list(menu.iter())) - 1, 'Duplicate key')
                self.assertEqual([n.get('Key') for n in menu],
                                 ['general', 'device', 'appearance', 'prayers', 'speech'])
                for parent, children in {
                    'general': ['language', 'calendar', 'general.online-mode'],
                    'language': ['language.interface'],
                    'language.interface': ['language.use-for-interface'],
                    'calendar': ['calendar.options'],
                    'calendar.options': ['calendar.epiphany-sunday', 'calendar.ascension-sunday',
                                         'calendar.corpus-christi-sunday', 'calendar.highlight-national'],
                    'reading.navigation': ['reading.arrow-options'],
                    'reading.arrow-options': ['reading.arrows-left', 'reading.down-arrow-only'],
                    'prayers': ['prayers.presentation', 'prayers.parts', 'prayers.readings',
                                'prayers.celebration', 'prayers.alternative-texts'],
                }.items():
                    self.assertEqual([n.get('Key') for n in actual[parent]], children, parent)
                for key, node in actual.items():
                    self.assertIn(node.tag, {'MenuGroup', 'MenuItem'}, key)
                    if key != 'language.interface':
                        label = node.attrib['Label']
                        self.assertTrue(label.strip(' /'), key)
                        self.assertNotIn('_text', label, key)
                        self.assertNotIn('<', label, key)
                        self.assertFalse(label[0].islower(), key)
                    if node.tag == 'MenuGroup':
                        self.assertTrue(len(node), key)
                        self.assertLessEqual(node.attrib.keys(), {'Key', 'Label'}, key)
                    else:
                        self.assertLessEqual(node.attrib.keys(), item_attributes, key)
                        self.assertIn(node.attrib['Control'], controls, key)
                        self.assertTrue({'Parameter', 'OptionRef', 'Handler'} & node.attrib.keys(), key)
                        self.assertFalse({'Parameter', 'OptionRef'} <= node.attrib.keys(), key)
                        self.assertTrue(all(n.tag == 'MenuGroup' for n in node), key)
                    if 'OptionRef' in node.attrib:
                        reference = node.attrib['OptionRef']
                        self.assertIsNotNone(root.find('Options/' + reference)
                                             if key == 'prayers.common'
                                             else root.find('Options/*/' + reference), key)
                        self.assertNotIn('Opt6', reference, key)
                    if 'ValuesRef' in node.attrib:
                        self.assertIsNotNone(root.find('.//' + node.attrib['ValuesRef']), key)
                # App-owned settings remain present even without a translation
                # of an unrelated liturgical option.
                for key in ('language.use-for-interface', 'general.online-mode', 'device.eink',
                            'device.volume-paging', 'device.keep-awake', 'device.do-not-disturb',
                            'device.lock-zoom', 'appearance.font', 'appearance.font-size',
                            'reading.navigation', 'speech.rate', 'speech.psalm-pauses', 'speech.help'):
                    self.assertEqual(actual[key].attrib['Handler'], key)
                self.assertEqual(actual['language'].attrib['Parameter'], 'j')
                self.assertEqual(actual['language'].attrib['ValuesRef'], 'SupportedLanguages')
                self.assertEqual(actual['language'].attrib['Handler'], 'language.select')
                self.assertEqual(actual['calendar'].attrib['Parameter'], 'k')
                self.assertEqual(actual['calendar'].attrib['ValuesRef'], 'LiturgicalCalendarValues')
                self.assertEqual(actual['prayers.common'].attrib['OptionRef'], 'Opt3Communia')
                self.assertEqual(actual['prayers.common'].attrib['ValueAttribute'], 'Id')
                seen.update({key: node.tag for key, node in actual.items()})
        self.assertEqual(list(seen.values()).count('MenuGroup'), 13)
        self.assertEqual(list(seen.values()).count('MenuItem'), 89)

    def test_language_specific_items(self):
        for language, root in self.exports.items():
            with self.subTest(language=language):
                menu = by_key(root.find('Menu'))
                self.assertEqual('readings.two-year-cycle' in menu, language == 'sk')
                self.assertEqual('readings.invert-cycle' in menu, language == 'sk')
                self.assertEqual('readings.alternatives' in menu, language == 'cz')
                self.assertEqual('alternatives.hymn-selection' in menu, language == 'cz')
                if language == 'cz':
                    self.assertNotIn('alternatives.readings-hymn', menu)
                if language == 'hu':
                    # An empty translated label suppresses only its menu entry.
                    self.assertNotIn('prayers.printed-edition', menu)
                    self.assertIsNotNone(root.find('Options/*/BitOpt0PrintedEdition'))

    def test_option_words_masks_overrides_and_decimal_places(self):
        variants = [{}, {'o0': '0', 'of0v': '1', 'o3': '1'},
                    {'o0': '2097151', 'o1': '1048575', 'o2': '131071',
                     'o5': '2097151', 'o6': '12345678901'}]
        for params in variants:
            with self.subTest(params=params):
                options = export(**params).find('Options')
                self.assertEqual([g.get('Name') for g in options],
                                 ['o0', 'o1', 'o2', 'o3', 'o5', 'o6'])
                self.assertEqual([len(g) for g in options], [21, 20, 17, 0, 21, 11])
                for group in options:
                    self.assertEqual(set(group.attrib), {'Name', 'Value', 'ForceName', 'Text'})
                    word = int(group.attrib['Value'])
                    for option in group:
                        self.assertEqual(set(option.attrib), {'Id', 'ForceName', 'Text'})
                        mask = int(option.attrib['Id'])
                        expected = word // mask % 10 if group.get('Name') == 'o6' else int(word & mask == mask)
                        self.assertEqual(int(option.text), expected, option.tag)
                decimal = options.find('Opt6AlternativesMultivalue/PlaceOpt6OurLordIntroMulti')
                # A decimal place above 32 bits must not be truncated on Android.
                self.assertIsNotNone(decimal)
                self.assertEqual(decimal.attrib['Id'], '10000000000')
        overridden = export(o0='0', of0v='1').find('Options/*/BitOpt0VerseNumbers')
        self.assertEqual(overridden.text, '1')

    def test_xml_escaping_and_empty_reset_values(self):
        menu = by_key(self.exports['en'].find('Menu'))
        self.assertIn('2nd & 8th', menu['calendar.epiphany-sunday'].attrib['Label'])
        self.assertIn('psalms & canticles', menu['speech.psalm-pauses'].attrib['Label'])
        for key in ('appearance.font', 'appearance.margin', 'appearance.line-height',
                    'appearance.background-day', 'appearance.background-night'):
            self.assertEqual(menu[key].attrib['ResetValue'], '')
        self.assertEqual(menu['appearance.font-size'].attrib['ResetValue'], '12')
        for key, parameter, default, minimum, maximum in (
                ('appearance.font-size', 'ff', '12', '4', '60'),
                ('appearance.margin', 'mm', '5', '1', '200'),
                ('appearance.line-height', 'lh', '130', '1', '500')):
            node = menu[key]
            self.assertEqual([node.get(a) for a in ('Parameter', 'Default', 'Min', 'Max')],
                             [parameter, default, minimum, maximum])

    def test_settings_without_calendar_day(self):
        root = export(d='', m='', r='')
        self.assertIsNotNone(root.find('Menu/MenuGroup/MenuItem'))
        self.assertIsNotNone(root.find('Options'))
        self.assertIsNotNone(root.find('.//LiturgicalCalendarValues'))


if __name__ == '__main__':
    unittest.main()
