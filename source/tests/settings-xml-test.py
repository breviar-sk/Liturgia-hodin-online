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
        # English UI labels are available even when English is not enabled as
        # a selectable prayer language in this build.
        cls.exports = {language: export(language) for language in set(languages + ['en'])}

    def test_structure_bindings_and_order(self):
        seen = {}
        controls = {'toggle', 'choice', 'color', 'number', 'font', 'action', 'preset'}
        item_attributes = {'Key', 'Label', 'Control', 'Parameter', 'OptionRef',
                           'ValuesRef', 'ValueAttribute', 'Handler', 'Default',
                           'ResetValue', 'Min', 'Max'}
        for language, root in self.exports.items():
            with self.subTest(language=language):
                menu = root.find('Menu')
                self.assertEqual(menu.attrib, {'Version': '1'})
                actual = by_key(menu)
                self.assertEqual(len(actual), len([node for node in menu.iter() if node.tag in ('MenuGroup', 'MenuItem')]), 'Duplicate key')
                self.assertEqual([n.get('Key') for n in menu],
                                 ['general', 'device', 'appearance', 'prayers', 'speech'])
                for parent, children in {
                    'general': ['language', 'calendar', 'general.online-mode'],
                    'language': ['language.interface'],
                    'language.interface': ['language.use-for-interface'],
                    'calendar': ['calendar.options'],
                    'calendar.options': ['calendar.epiphany-sunday', 'calendar.ascension-sunday',
                                         'calendar.corpus-christi-sunday', 'calendar.highlight-national'],
                    'appearance': ['appearance.font-margins', 'appearance.colors',
                                   'appearance.buttons', 'appearance.other'],
                    'device': ['device.navigation', 'device.eink', 'device.volume-paging',
                               'device.keep-awake', 'device.do-not-disturb', 'device.lock-zoom'],
                    'device.navigation': ['device.reading-navigation'],
                    'device.reading-navigation': ['device.arrow-options'],
                    'device.arrow-options': ['device.arrows-left', 'device.down-arrow-only'],
                    'prayers': ['prayers.inline-options', 'prayers.presentation', 'prayers.parts',
                                'prayers.celebration', 'prayers.other',
                                'prayers.alternatives-inline', 'prayers.alternatives'],
                    'prayers.alternatives.invitatory': ['prayers.alternatives.invitatory.psalm-95',
                                                      'prayers.alternatives.invitatory.antiphon'],
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
                        self.assertLessEqual(node.attrib.keys(), {'Key', 'Label', 'Control'}, key)
                    else:
                        self.assertLessEqual(node.attrib.keys(), item_attributes, key)
                        self.assertIn(node.attrib['Control'], controls, key)
                        self.assertTrue(node.get('Control') == 'preset' or {'Parameter', 'OptionRef', 'Handler'} & node.attrib.keys(), key)
                        self.assertFalse({'Parameter', 'OptionRef'} <= node.attrib.keys(), key)
                        self.assertTrue(all(n.tag == ('Set' if node.get('Control') == 'preset' else 'MenuGroup') for n in node), key)
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
                            'device.reading-navigation', 'speech.rate', 'speech.psalm-pauses', 'speech.help'):
                    self.assertEqual(actual[key].attrib['Handler'], key)
                self.assertEqual(actual['language'].attrib['Parameter'], 'j')
                self.assertEqual(actual['language'].attrib['ValuesRef'], 'SupportedLanguages')
                self.assertEqual(actual['language'].attrib['Handler'], 'language.select')
                self.assertEqual(actual['calendar'].attrib['Parameter'], 'k')
                self.assertEqual(actual['calendar'].attrib['ValuesRef'], 'LiturgicalCalendarValues')
                self.assertEqual(actual['prayers.common'].attrib['OptionRef'], 'Opt3Communia')
                self.assertEqual(actual['prayers.common'].attrib['ValueAttribute'], 'Id')
                seen.update({key: node.tag for key, node in actual.items()})
        self.assertEqual(list(seen.values()).count('MenuGroup'), 26)
        self.assertEqual(list(seen.values()).count('MenuItem'), 99)

    def test_palette_submenus_and_complete_presets(self):
        for root in self.exports.values():
            menu = by_key(root.find('Menu'))
            self.assertEqual([node.get('Key') for node in menu['appearance.colors']],
                             ['appearance.night-mode', 'appearance.colors.day', 'appearance.colors.night'])
            for mode, suffix in [('day', '0'), ('night', '1')]:
                prefix = 'appearance.colors.' + mode
                self.assertEqual(menu[prefix].get('Control'), 'submenu')
                for role, parameter in [('text', 'ct'), ('rubric', 'cr'), ('background', 'c')]:
                    node = menu[prefix + '.' + role]
                    self.assertEqual(node.get('Control'), 'color')
                    self.assertEqual(node.get('Parameter'), parameter + suffix)
                    self.assertEqual(node.get('ResetValue'), '')
                for preset in menu[prefix + '.presets']:
                    values = {node.get('Parameter'): node.get('Value') for node in preset}
                    self.assertEqual(set(values), {'ct' + suffix, 'cr' + suffix, 'c' + suffix})
                defaults = {node.get('Value') for node in menu[prefix + '.default']}
                self.assertEqual(defaults, {''})
            self.assertEqual({n.get('Parameter'): n.get('Value') for n in menu['appearance.colors.day.yellow']},
                             {'ct0': '', 'cr0': '', 'c0': 'ffffcc'})
            self.assertEqual({n.get('Parameter'): n.get('Value') for n in menu['appearance.colors.day.high-contrast']},
                             {'ct0': '000000', 'cr0': '800000', 'c0': 'ffffff'})
            self.assertEqual({n.get('Parameter'): n.get('Value') for n in menu['appearance.colors.night.high-contrast']},
                             {'ct1': 'ffffff', 'cr1': 'ffff00', 'c1': '000000'})

    def test_language_specific_items(self):
        for language, root in self.exports.items():
            with self.subTest(language=language):
                menu = by_key(root.find('Menu'))
                readings = 'prayers.alternatives.readings.'
                self.assertEqual(readings + 'two-year-cycle' in menu, language == 'sk')
                self.assertEqual(readings + 'invert-cycle' in menu, language == 'sk')
                self.assertEqual(readings + 'cz-alternatives' in menu, language == 'cz')
                self.assertEqual('prayers.alternatives.cz-hymn-selection' in menu, language == 'cz')
                self.assertEqual('prayers.alternatives.first-vespers' in menu, language != 'cz')
                if language != 'cz':
                    self.assertEqual([n.get('Key') for n in menu['prayers.alternatives.first-vespers']],
                                     ['alternatives.first-vespers-hymn'])
                if language == 'cz':
                    self.assertNotIn(readings + 'hymn-alternatives', menu)
                if language == 'hu':
                    # An empty translated label suppresses only its menu entry.
                    self.assertNotIn('prayers.printed-edition', menu)
                    self.assertIsNotNone(root.find('Options/*/BitOpt0PrintedEdition'))

    def test_option_words_masks_overrides_and_decimal_places(self):
        variants = [{}, {'o0': '0', 'of0v': '1', 'o3': '1'},
                    {'o0': '2097151', 'o1': '2097151', 'o2': '131071',
                     'o5': '2097151', 'o6': '12345678901'}]
        for params in variants:
            with self.subTest(params=params):
                options = export(**params).find('Options')
                self.assertEqual([g.get('Name') for g in options],
                                 ['o0', 'o1', 'o2', 'o3', 'o5', 'o6'])
                self.assertEqual([len(g) for g in options], [21, 21, 17, 0, 21, 11])
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

    def test_prayer_buttons_preserve_saved_url_options(self):
        # The renamed XML option must still use the same bit and short URL
        # parameter, so existing reader settings and links retain their effect.
        for value in ('0', '1'):
            with self.subTest(value=value):
                root = export(o2='0', of2nav=value)
                option = root.find("Options/*[@Name='o2']/BitOpt2PrayerButtons")
                self.assertIsNotNone(option)
                self.assertEqual(option.attrib['Id'], '32')
                self.assertEqual(option.attrib['ForceName'], 'of2nav')
                self.assertEqual(option.text, value)
                menu = by_key(root.find('Menu'))
                self.assertEqual(menu['appearance.prayer-buttons'].attrib['OptionRef'], option.tag)

    def test_penitential_act_has_an_independent_bit_and_override(self):
        for rubrics in (0, 2):
            for value in (0, 1):
                with self.subTest(rubrics=rubrics, value=value):
                    root = export(o1=rubrics | ((1 - value) * 1048576), of1uk=value)
                    option = root.find('Options/*/BitOpt1ComplinePenitentialAct')
                    self.assertEqual(option.attrib['Id'], '1048576')
                    self.assertEqual(option.attrib['ForceName'], 'of1uk')
                    self.assertEqual(option.text, str(value))
                    self.assertEqual(root.find('Options/*/BitOpt1Rubrics').text, str(rubrics // 2))
                    menu = by_key(root.find('Menu'))
                    self.assertEqual(menu['prayers.penitential-act'].attrib['OptionRef'], option.tag)
        self.assertNotIn('prayers.penitential-act', by_key(export('hu', dl='sk').find('Menu')))

    def test_english_labels_and_empty_reset_values(self):
        menu = by_key(self.exports['en'].find('Menu'))
        self.assertIn('Jan 2nd and 8th', menu['calendar.epiphany-sunday'].attrib['Label'])
        self.assertIn('psalms and canticles', menu['speech.psalm-pauses'].attrib['Label'])
        for key in ('appearance.font', 'appearance.margin', 'appearance.line-height',
                    'appearance.colors.day.background', 'appearance.colors.night.background'):
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

    def test_display_language_never_changes_structure_or_state(self):
        # Include editions with different calendars, empty labels and options.
        for prayer in ('sk', 'cz', 'c2', 'la', 'hu', 'is', 'en'):
            baseline = export(prayer, o0='12345', o3='1', o5='17')
            for display in ('sk', 'cz', 'la', 'hu', 'is', 'en', 'ru', 'by', 'az', ''):
                with self.subTest(prayer=prayer, display=display):
                    translated = export(prayer, dl=display, o0='12345', o3='1', o5='17')
                    original_nodes = list(baseline.iter())
                    new_nodes = list(translated.iter())
                    self.assertEqual(len(original_nodes), len(new_nodes))
                    for before, after in zip(original_nodes, new_nodes):
                        self.assertEqual(before.tag, after.tag)
                        self.assertEqual({k: v for k, v in before.attrib.items() if k not in ('Label', 'Text')},
                                         {k: v for k, v in after.attrib.items() if k not in ('Label', 'Text')})
                        # Only text in these settings catalogs may change.
                        if before.tag not in ('LiturgicalCelebrationCommunia', 'Opt3Communia',
                                              'LiturgicalSeason', 'LiturgicalCelebrationType', 'LiturgicalCelebrationColor'):
                            self.assertEqual(before.text, after.text, before.tag)
                    for path in ('SupportedLanguages', './/LiturgicalCalendarValues', './/LiturgicalYearLetterValues'):
                        self.assertEqual(ET.tostring(baseline.find(path)), ET.tostring(translated.find(path)))
                    self.assertEqual([bool((n.text or '').strip()) for n in baseline.find('.//LiturgicalCelebrationCommuniaValues')],
                                     [bool((n.text or '').strip()) for n in translated.find('.//LiturgicalCelebrationCommuniaValues')])
                    for node in translated.find('Menu').iter():
                        self.assertNotIn('_text', node.get('Label', ''))

    def test_display_labels_and_prayer_specific_captions(self):
        base = export('sk')
        translated = export('sk', dl='en')
        menu = by_key(translated.find('Menu'))
        self.assertEqual(menu['language'].get('Label'), 'Language')
        self.assertEqual(menu['prayers.verse-numbers'].get('Label'), 'Verse numbering')
        # Generic captions were made translatable upstream; edition-specific
        # hymn titles must still come from the prayer language.
        english = by_key(self.exports['en'].find('Menu'))
        for key in ('prayers.references', 'prayers.alternatives.invitatory.psalm-95',
                    'prayers.alternatives.daytime.psalm-122'):
            self.assertEqual(menu[key].get('Label'), english[key].get('Label'))
        for key in ('prayers.alternatives.compline-hymn', 'prayers.alternatives.easter-morning-hymn'):
            self.assertEqual(menu[key].get('Label'), by_key(base.find('Menu'))[key].get('Label'))
        self.assertEqual(translated.find('Options/*/BitOpt0VerseNumbers').get('Text'), 'verse numbering')
        self.assertEqual(translated.find(".//LiturgicalCelebrationCommunia[@Id='1']").text, 'pastors: priests')
        self.assertEqual(by_key(export('sk', dl='unknown').find('Menu'))['language'].get('Label'), 'Language')
        self.assertEqual(ET.tostring(export('sk', dl='').find('Menu')), ET.tostring(base.find('Menu')))

    def test_completed_ui_translations_do_not_enable_prayer_options(self):
        for prayer, key, tag in (
                ('la', 'prayers.printed-edition', 'BitOpt0PrintedEdition'),
                ('hu', 'prayers.marian-antiphons', 'BitOpt1ComplineMaryAnt')):
            for display in ('', 'sk', 'en'):
                with self.subTest(prayer=prayer, display=display):
                    root = export(prayer, dl=display)
                    self.assertNotIn(key, by_key(root.find('Menu')))
                    self.assertEqual(root.find('Options/*/' + tag).get('Text'), '')


if __name__ == '__main__':
    unittest.main()
