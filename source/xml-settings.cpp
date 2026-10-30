// Settings XML shared by the native apps. Menu v1 uses semantic keys, nested
// groups, references to exported options/values, and native-adapter handlers.
// Options remains compatible with the existing iOS/Android API.
#include "xml-settings.h"
#include "breviar.h"
#include "mydefs.h"
#include "myexpt.h"
#include "mystring.h"
#include "settings-text.h"

#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

namespace {

using Attributes = std::vector<std::pair<std::string, std::string>>;

// A small XML value tree keeps nesting visible in the catalog below. All strings
// are owned; serialization has a single escaping boundary and uses Export(), so
// it works with both the CGI stream and Android's in-memory output.
struct Element {
	std::string name;
	Attributes attributes;
	std::vector<Element> children;
	std::string text;
};

std::string escapeXml(const std::string& text) {
	std::string result;
	for (char c : text) {
		switch (c) {
		case '&': result += "&amp;"; break;
		case '<': result += "&lt;"; break;
		case '>': result += "&gt;"; break;
		case '"': result += "&quot;"; break;
		case '\'': result += "&apos;"; break;
		default: result += c; break;
		}
	}
	return result;
}

void appendXml(std::string& xml, const Element& element, unsigned depth = 0) {
	if (element.name.empty()) return;
	const std::string indent(depth * 2, ' ');
	xml += indent + "<" + element.name;
	for (const auto& attribute : element.attributes) {
		xml += " " + attribute.first + "=\"" + escapeXml(attribute.second) + "\"";
	}
	if (element.children.empty() && element.text.empty()) {
		xml += " />\n";
		return;
	}
	xml += ">";
	if (!element.children.empty()) {
		xml += "\n";
		for (const auto& child : element.children) appendXml(xml, child, depth + 1);
		xml += indent;
	}
	xml += escapeXml(element.text) + "</" + element.name + ">\n";
}

std::string localized(const char* const* labels) {
	return labels && labels[_global_jazyk] ? labels[_global_jazyk] : "";
}

struct Option {
	const char* element;
	unsigned long long mask;
	const char* forceName;
	const char* const* labels;
	const char* const* alternativeLabels;

	Option(const char* element, unsigned long long mask, const char* forceName,
		const char* const* labels, const char* const* alternativeLabels = nullptr)
		: element(element), mask(mask), forceName(forceName), labels(labels),
		  alternativeLabels(alternativeLabels) {}

	std::string label() const {
		return localized(labels) + (alternativeLabels ? " / " + localized(alternativeLabels) : "");
	}
};

struct OptionGroup {
	short index;
	const char* element;
	const char* parameter;
	const char* forceName;
	const char* const* labels;
	std::vector<Option> options;
};

// One source of truth for legacy option metadata and the labels of Menu toggles.
// Keep even unnamed/inapplicable bits here: clients use Options for state and
// round trips. Only the presentation catalog filters out unavailable labels.
const OptionGroup optionGroups[] = {
	{OPT_0_SPECIALNE, XML_OPT_0_SPECIALNE, STR_OPT_0, STR_FORCE_OPT_0, html_text_opt_0_kalendar, {
		{XML_BIT_OPT_0_VERSE, BIT_OPT_0_VERSE, STR_FORCE_BIT_OPT_0_VERSE, html_text_opt_0_verse},
		{XML_BIT_OPT_0_REFERENCIE, BIT_OPT_0_REFERENCIE, STR_FORCE_BIT_OPT_0_REF, html_text_opt_0_referencie},
		{XML_BIT_OPT_0_CITANIA, BIT_OPT_0_CITANIA, STR_FORCE_BIT_OPT_0_CIT, html_text_opt_0_citania},
		{XML_BIT_OPT_0_ZJAVENIE_PANA_NEDELA, BIT_OPT_0_ZJAVENIE_PANA_NEDELA, STR_FORCE_BIT_OPT_0_ZJAV_NED, html_text_opt_0_zjv_ne},
		{XML_BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA, STR_FORCE_BIT_OPT_0_NAN_NED, html_text_opt_0_nan_ne},
		{XML_BIT_OPT_0_TELAKRVI_NEDELA, BIT_OPT_0_TELAKRVI_NEDELA, STR_FORCE_BIT_OPT_0_TK_NED, html_text_opt_0_tk_ne},
		{XML_BIT_OPT_0_FONT_NORMAL, BIT_OPT_0_FONT_NORMAL, STR_FORCE_BIT_OPT_0_FONT_NORMAL, html_text_opt_0_font_normal},
		{XML_BIT_OPT_0_BUTTONS_ORDER, BIT_OPT_0_BUTTONS_ORDER, STR_FORCE_BIT_OPT_0_BUTTONS_ORDER, html_text_opt_0_buttons_order},
		{XML_BIT_OPT_0_VOICE_OUTPUT, BIT_OPT_0_VOICE_OUTPUT, STR_FORCE_BIT_OPT_0_VOICE_OUTPUT, html_text_opt_0_voice_output},
		{XML_BIT_OPT_0_FOOTNOTES, BIT_OPT_0_FOOTNOTES, STR_FORCE_BIT_OPT_0_FOOTNOTES, html_text_opt_0_footnotes},
		{XML_BIT_OPT_0_TRANSPARENT_NAV, BIT_OPT_0_TRANSPARENT_NAV, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV, html_text_opt_0_transparent_nav},
		{XML_BIT_OPT_0_ZALMY_FULL_TEXT, BIT_OPT_0_ZALMY_FULL_TEXT, STR_FORCE_BIT_OPT_0_ZALMY_FULL_TEXT, html_text_opt_0_zalmy_full_text},
		{XML_BIT_OPT_0_REF_BIBLE_COM, BIT_OPT_0_REF_BIBLE_COM, STR_FORCE_BIT_OPT_0_REF_BIBLE_COM, html_text_opt_0_ref_bible_com},
		{XML_BIT_OPT_0_ITALICS_CONDITIONAL, BIT_OPT_0_ITALICS_CONDITIONAL, STR_FORCE_BIT_OPT_0_ITALICS_CONDITIONAL, html_text_opt_0_italics_cond},
		{XML_BIT_OPT_0_PRINTED_EDITION, BIT_OPT_0_PRINTED_EDITION, STR_FORCE_BIT_OPT_0_PRINTED_EDITION, html_text_opt_0_printed_edition},
		{XML_BIT_OPT_0_USE_TWO_YEARS_CYCLE, BIT_OPT_0_USE_TWO_YEARS_CYCLE, STR_FORCE_BIT_OPT_0_USE_TWO_YEARS_CYCLE, html_text_opt_0_use_two_years_cycle},
		{XML_BIT_OPT_0_TWO_YEARS_CYCLE_INVERT, BIT_OPT_0_TWO_YEARS_CYCLE_INVERT, STR_FORCE_BIT_OPT_0_TWO_YEARS_CYCLE_INVERT, html_text_opt_0_two_years_cycle_invert},
		{XML_BIT_OPT_0_ALTERNATIVE_READINGS, BIT_OPT_0_ALTERNATIVE_READINGS, STR_FORCE_BIT_OPT_0_ALTERNATIVE_READINGS, html_text_opt_0_alternative_readings},
		{XML_BIT_OPT_0_TRANSPARENT_NAV_LEFT, BIT_OPT_0_TRANSPARENT_NAV_LEFT, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV_LEFT, html_text_opt_0_transparent_nav_left},
		{XML_BIT_OPT_0_SIDE_NAVIGATION, BIT_OPT_0_SIDE_NAVIGATION, STR_FORCE_BIT_OPT_0_SIDE_NAVIGATION, html_text_opt_0_side_navigation},
		{XML_BIT_OPT_0_TRANSPARENT_NAV_DOWN_ONLY, BIT_OPT_0_TRANSPARENT_NAV_DOWN_ONLY, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV_DOWN_ONLY, html_text_opt_0_transparent_nav_down_only},
	}},
	{OPT_1_CASTI_MODLITBY, XML_OPT_1_CASTI_MODLITBY, STR_OPT_1, STR_FORCE_OPT_1, html_text_opt_1_nemenne_sucasti, {
		{XML_BIT_OPT_1_TEDEUM, BIT_OPT_1_TEDEUM, STR_FORCE_BIT_OPT_1_TD, html_text_opt_1_tedeum},
		{XML_BIT_OPT_1_RUBRIKY, BIT_OPT_1_RUBRIKY, STR_FORCE_BIT_OPT_1_RUB, html_text_opt_1_rubriky},
		{XML_BIT_OPT_1_CHVALOSPEVY, BIT_OPT_1_CHVALOSPEVY, STR_FORCE_BIT_OPT_1_CHV, html_text_opt_1_chvalospevy},
		{XML_BIT_OPT_1_SLAVA_OTCU, BIT_OPT_1_SLAVA_OTCU, STR_FORCE_BIT_OPT_1_SL, html_text_opt_1_slava_otcu},
		{XML_BIT_OPT_1_OTCENAS, BIT_OPT_1_OTCENAS, STR_FORCE_BIT_OPT_1_OT, html_text_opt_1_otcenas},
		{XML_BIT_OPT_1_MCD_DOPLNKOVA, BIT_OPT_1_MCD_DOPLNKOVA, STR_FORCE_BIT_OPT_1_MCD_DOPLNKOVA, html_text_opt_1_mcd_zalmy_ine},
		{XML_BIT_OPT_1_PC_VIGILIA, BIT_OPT_1_PC_VIGILIA, STR_FORCE_BIT_OPT_1_VIGILIA, html_text_opt_1_vigilia},
		{XML_BIT_OPT_1_SPOMIENKA_SPOL_CAST, BIT_OPT_1_SPOMIENKA_SPOL_CAST, STR_FORCE_BIT_OPT_1_SPOMIENKA_SPOL_CAST, html_text_opt_1_spomienka_spolcast},
		{XML_BIT_OPT_1_PLNE_RESP, BIT_OPT_1_PLNE_RESP, STR_FORCE_BIT_OPT_1_PLNE_RESP, html_text_opt_1_plne_resp},
		{XML_BIT_OPT_1_ZALM95, BIT_OPT_1_ZALM95, STR_FORCE_BIT_OPT_1_ZALM95, html_text_opt_1_zalm95},
		{XML_BIT_OPT_1_PROSBY_ZVOLANIE, BIT_OPT_1_PROSBY_ZVOLANIE, STR_FORCE_BIT_OPT_1_PROSBY_ZVOLANIE, html_text_opt_1_prosby_zvolanie},
		{XML_BIT_OPT_1_SKRY_POPIS, BIT_OPT_1_SKRY_POPIS, STR_FORCE_BIT_OPT_1_SKRY_POPIS, html_text_opt_1_skryt_popis_svaty},
		{XML_BIT_OPT_1_ZOBRAZ_SPOL_CAST, BIT_OPT_1_ZOBRAZ_SPOL_CAST, STR_FORCE_BIT_OPT_1_ZOBRAZ_SPOL_CAST, html_text_opt_1_spolc_svaty},
		{XML_BIT_OPT_1_VESP_KRATSIE_PROSBY, BIT_OPT_1_VESP_KRATSIE_PROSBY, STR_FORCE_BIT_OPT_1_VESP_KRATSIE_PROSBY, html_text_opt_1_vesp_kratsie_prosby},
		{XML_BIT_OPT_1_MCD_ZALTAR_TRI, BIT_OPT_1_MCD_ZALTAR_TRI, STR_FORCE_BIT_OPT_1_MCD_ZALTAR_TRI, html_text_opt_1_mcd_zalmy_tri},
		{XML_BIT_OPT_1_ZAVER, BIT_OPT_1_ZAVER, STR_FORCE_BIT_OPT_1_ZAVER, html_text_opt_1_zaver},
		{XML_BIT_OPT_1_OVERRIDE_STUP_SLAV, BIT_OPT_1_OVERRIDE_STUP_SLAV, STR_FORCE_BIT_OPT_1_OVERRIDE_STUP_SLAV, html_text_opt_1_override_stupen_slavenia},
		{XML_BIT_OPT_1_STUP_SVIATOK_SLAVNOST, BIT_OPT_1_STUP_SVIATOK_SLAVNOST, STR_FORCE_BIT_OPT_1_STUP_SVIATOK_SLAVNOST, html_text_opt_1_slavit_ako_slavnost},
		{XML_BIT_OPT_1_KOMPL_MARIA_ANT, BIT_OPT_1_KOMPL_MARIA_ANT, STR_FORCE_BIT_OPT_1_KOMPL_MARIA_ANT, html_text_opt_1_maria_ant},
		{XML_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, STR_FORCE_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, html_text_opt_1_otcenas_uvod},
	}},
	{OPT_2_HTML_EXPORT, XML_OPT_2_HTML_EXPORT, STR_OPT_2, STR_FORCE_OPT_2, html_text_opt_2_html_export, {
		{XML_BIT_OPT_2_ISO_DATUM, BIT_OPT_2_ISO_DATUM, STR_FORCE_BIT_OPT_2_ISO_DATUM, html_text_opt_2_iso_datum},
		{XML_BIT_OPT_2_BUTTON_PRVE_VESPERY, BIT_OPT_2_BUTTON_PRVE_VESPERY, STR_FORCE_BIT_OPT_2_PRVE_VESPERY, html_text_opt_2_prve_vespery},
		{XML_BIT_OPT_2_FONT_FAMILY, BIT_OPT_2_FONT_FAMILY, STR_FORCE_BIT_OPT_2_FONT_FAMILY, html_text_opt_2_font_family},
		{XML_BIT_OPT_2_FONT_NAME_CHOOSER, BIT_OPT_2_FONT_NAME_CHOOSER, STR_FORCE_BIT_OPT_2_FONT_NAME_CHOOSER, html_text_font_name_simple},
		{XML_BIT_OPT_2_FONT_SIZE_CHOOSER, BIT_OPT_2_FONT_SIZE_CHOOSER, STR_FORCE_BIT_OPT_2_FONT_SIZE, html_text_font_size},
		{XML_BIT_OPT_2_PRAYER_BUTTONS, BIT_OPT_2_PRAYER_BUTTONS, STR_FORCE_BIT_OPT_2_PRAYER_BUTTONS, html_text_opt_2_prayer_buttons},
		{XML_BIT_OPT_2_HIDE_NAVIG_BUTTONS, BIT_OPT_2_HIDE_NAVIG_BUTTONS, STR_FORCE_BIT_OPT_2_HIDE_NAVIG_BUTTONS, nullptr },
		{XML_BIT_OPT_2_TEXT_WRAP, BIT_OPT_2_TEXT_WRAP, STR_FORCE_BIT_OPT_2_TEXT_WRAP, html_text_opt_2_textwrap},
		{XML_BIT_OPT_2_BUTTONY_USPORNE, BIT_OPT_2_BUTTONY_USPORNE, STR_FORCE_BIT_OPT_2_BUTTONY_USPORNE, html_text_opt_2_buttons_usporne},
		{XML_BIT_OPT_2_NOCNY_REZIM, BIT_OPT_2_NOCNY_REZIM, STR_FORCE_BIT_OPT_2_NOCNY_REZIM, html_text_opt_2_nocny_rezim},
		{XML_BIT_OPT_2_ROZNE_MOZNOSTI, BIT_OPT_2_ROZNE_MOZNOSTI, STR_FORCE_BIT_OPT_2_ROZNE_MOZNOSTI, html_text_opt_2_moznosti},
		{XML_BIT_OPT_2_HIDE_KALENDAR, BIT_OPT_2_HIDE_KALENDAR, STR_FORCE_BIT_OPT_2_HIDE_KALENDAR, nullptr},
		{XML_BIT_OPT_2_HIDE_OPTIONS1, BIT_OPT_2_HIDE_OPTIONS1, STR_FORCE_BIT_OPT_2_HIDE_OPTIONS1, nullptr},
		{XML_BIT_OPT_2_HIDE_OPTIONS2, BIT_OPT_2_HIDE_OPTIONS2, STR_FORCE_BIT_OPT_2_HIDE_OPTIONS2, nullptr},
		{XML_BIT_OPT_2_ALTERNATIVES, BIT_OPT_2_ALTERNATIVES, STR_FORCE_BIT_OPT_2_ALTERNATIVES, html_text_opt_2_alternatives},
		{XML_BIT_OPT_2_SHOW_DEFAULT_CALENDAR, BIT_OPT_2_SHOW_DEFAULT_CALENDAR, STR_FORCE_BIT_OPT_2_SHOW_DEFAULT_CALENDAR, html_text_opt_2_show_defalut_calendar},
		{XML_BIT_OPT_2_ROUNDED_CORNERS, BIT_OPT_2_ROUNDED_CORNERS, STR_FORCE_BIT_OPT_2_ROUNDED_CORNERS, html_text_opt_2_rounded_corners},
	}},
	{OPT_3_SPOLOCNA_CAST, XML_OPT_3_SPOLOCNA_CAST, STR_OPT_3, STR_FORCE_OPT_3, html_text_spol_casti_vziat_zo, {

	}},
	{OPT_5_ALTERNATIVES, XML_OPT_5_ALTERNATIVES, STR_OPT_5, STR_FORCE_OPT_5, html_text_opt_2_alternatives, {
		{XML_BIT_OPT_5_HYMNUS_KOMPL, BIT_OPT_5_HYMNUS_KOMPL, STR_FORCE_BIT_OPT_5_HYMNUS_KOMPL, html_text_opt_5_KomplHymnusA, html_text_opt_5_KomplHymnusB},
		{XML_BIT_OPT_5_HYMNUS_PC, BIT_OPT_5_HYMNUS_PC, STR_FORCE_BIT_OPT_5_HYMNUS_PC, html_text_opt_5_PCHymnusI, html_text_opt_5_PCHymnusII},
		{XML_BIT_OPT_5_HYMNUS_MCD_PREDPOL, BIT_OPT_5_HYMNUS_MCD_PREDPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_PREDPOL, html_text_opt_5_MCDPredHymnus1, html_text_opt_5_MCDPredHymnus2},
		{XML_BIT_OPT_5_HYMNUS_MCD_NAPOL, BIT_OPT_5_HYMNUS_MCD_NAPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_NAPOL, html_text_opt_5_MCDNaHymnus1, html_text_opt_5_MCDNaHymnus2},
		{XML_BIT_OPT_5_HYMNUS_MCD_POPOL, BIT_OPT_5_HYMNUS_MCD_POPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_POPOL, html_text_opt_5_MCDPoHymnus1, html_text_opt_5_MCDPoHymnus2},
		{XML_BIT_OPT_5_DOPLNK_PSALM_122_129, BIT_OPT_5_DOPLNK_PSALM_122_129, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_122_129, html_text_opt_5_DPsalmZ122_129},
		{XML_BIT_OPT_5_DOPLNK_PSALM_127_131, BIT_OPT_5_DOPLNK_PSALM_127_131, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_127_131, html_text_opt_5_DPsalmZ127_131},
		{XML_BIT_OPT_5_DOPLNK_PSALM_126_129, BIT_OPT_5_DOPLNK_PSALM_126_129, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_126_129, html_text_opt_5_DPsalmZ126_129},
		{XML_BIT_OPT_5_HYMNUS_VN_PC, BIT_OPT_5_HYMNUS_VN_PC, STR_FORCE_BIT_OPT_5_HYMNUS_VN_PC, html_text_opt_5_PCHymnusVNnedela, html_text_opt_5_PCHymnusVNferia},
		{XML_BIT_OPT_5_HYMNUS_VN_RCH, BIT_OPT_5_HYMNUS_VN_RCH, STR_FORCE_BIT_OPT_5_HYMNUS_VN_RCH, html_text_opt_5_RChHymnusVNnedela, html_text_opt_5_RChHymnusVNferia},
		{XML_BIT_OPT_5_HYMNUS_VN_VESP, BIT_OPT_5_HYMNUS_VN_VESP, STR_FORCE_BIT_OPT_5_HYMNUS_VN_VESP, html_text_opt_5_VespHymnusVNnedela, html_text_opt_5_VespHymnusVNferia},
		{XML_BIT_OPT_5_HYMNUS_1VESP, BIT_OPT_5_HYMNUS_1VESP, STR_FORCE_BIT_OPT_5_HYMNUS_1VESP, html_text_opt_5_1VHymnusNe, html_text_opt_5_1VHymnusPC},
		{XML_BIT_OPT_5_POPOL_STREDA_PSALMODIA, BIT_OPT_5_POPOL_STREDA_PSALMODIA, STR_FORCE_BIT_OPT_5_POPOL_STREDA_PSALMODIA, html_text_opt_5_PopolStrPsalm_4STR, html_text_opt_5_PopolStrPsalm_3PI},
		{XML_BIT_OPT_5_CZ_HYMNY_VYBER, BIT_OPT_5_CZ_HYMNY_VYBER, STR_FORCE_BIT_OPT_5_CZ_HYMNY_VYBER, html_text_opt_5_CZhymnyNORMAL, html_text_opt_5_CZhymnyRENC},
		{XML_BIT_OPT_5_OFF_DEF_PSALM_146_150, BIT_OPT_5_OFF_DEF_PSALM_146_150, STR_FORCE_BIT_OPT_5_OFF_DEF_PSALM_146_150, html_text_opt_5_OffDefZ146_150},
		{XML_BIT_OPT_5_ZAVER_KNAZ_DIAKON, BIT_OPT_5_ZAVER_KNAZ_DIAKON, STR_FORCE_BIT_OPT_5_ZAVER_KNAZ_DIAKON, html_text_opt_5_zaver_knaz_diakon},
		{XML_BIT_OPT_5_INVITAT_ANT_WRAP_ONLY, BIT_OPT_5_INVITAT_ANT_WRAP_ONLY, STR_FORCE_BIT_OPT_5_INVITAT_ANT_WRAP_ONLY, html_text_opt_5_invitat_ant_wrap_only},
		{XML_BIT_OPT_5_OCR_34_HYMNS, BIT_OPT_5_OCR_34_HYMNS, STR_FORCE_BIT_OPT_5_OCR_34_HYMNS, html_text_opt_5_OCR34Hymns},
		{XML_BIT_OPT_5_KOMPLETORIUM_OKTAVA, BIT_OPT_5_KOMPLETORIUM_OKTAVA, STR_FORCE_BIT_OPT_5_KOMPLETORIUM_OKTAVA, html_text_opt_5_KomplOkt1, html_text_opt_5_KomplOkt2},
		{XML_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, STR_FORCE_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, html_text_opt_5_ZelStvPsalm_2STV, html_text_opt_5_ZelStvPsalm_3PI},
		{XML_BIT_OPT_5_LENT_5_HYMNS, BIT_OPT_5_POST_5_HYMNS, STR_FORCE_BIT_OPT_5_POST_5_HYMNS, html_text_opt_5_Lent5Hymns},
	}},
	{OPT_6_ALTERNATIVES_MULTI, XML_OPT_6_ALTERNATIVES_MULTI, STR_OPT_6, STR_FORCE_OPT_6, html_text_opt_6_alternatives_multi, {
		{XML_PLACE_OPT_6_HYMNUS_MULTI, BASE_OPT_6_HYMNUS_MULTI, STR_FORCE_PLACE_OPT_6_HYMNUS_MULTI, html_text_opt_6_alternatives_multi_hymnus},
		{XML_PLACE_OPT_6_PSALM_MULTI, BASE_OPT_6_PSALM_MULTI, STR_FORCE_PLACE_OPT_6_PSALM_MULTI, html_text_opt_6_alternatives_multi_psalm},
		{XML_PLACE_OPT_6_CITANIE2_MULTI, BASE_OPT_6_CITANIE2_MULTI, STR_FORCE_PLACE_OPT_6_CITANIE2_MULTI, html_text_opt_6_alternatives_multi_citanie},
		{XML_PLACE_OPT_6_CITANIE1_MULTI, BASE_OPT_6_CITANIE1_MULTI, STR_FORCE_PLACE_OPT_6_CITANIE1_MULTI, html_text_opt_6_alternatives_multi_citanie},
		{XML_PLACE_OPT_6_ANTIFONA_MULTI, BASE_OPT_6_ANTIFONA_MULTI, STR_FORCE_PLACE_OPT_6_ANTIFONA_MULTI, html_text_opt_6_alternatives_multi_antifona},
		{XML_PLACE_OPT_6_MODLITBA_MULTI, BASE_OPT_6_MODLITBA_MULTI, STR_FORCE_PLACE_OPT_6_MODLITBA_MULTI, html_text_opt_6_alternatives_multi_modlitba},
		{XML_PLACE_OPT_6_PROSBY_MULTI, BASE_OPT_6_PROSBY_MULTI, STR_FORCE_PLACE_OPT_6_PROSBY_MULTI, html_text_opt_6_alternatives_multi_prosby},
		{XML_PLACE_OPT_6_MARIA_ANT_MULTI, BASE_OPT_6_MARIA_ANT_MULTI, STR_FORCE_PLACE_OPT_6_MARIA_ANT_MULTI, html_text_opt_6_alternatives_multi_maria_ant},
		{XML_PLACE_OPT_6_KRESP_MULTI, BASE_OPT_6_KRESP_MULTI, STR_FORCE_PLACE_OPT_6_KRESP_MULTI, html_text_opt_6_alternatives_multi_kresp},
		{XML_PLACE_OPT_6_KCIT_RESP_MULTI, BASE_OPT_6_KCIT_RESP_MULTI, STR_FORCE_PLACE_OPT_6_KCIT_RESP_MULTI, html_text_opt_6_alternatives_multi_kcit_resp},
		{XML_PLACE_OPT_6_OTCENAS_UVOD_MULTI, BASE_OPT_6_OTCENAS_UVOD_MULTI, STR_FORCE_PLACE_OPT_6_OTCENAS_UVOD_MULTI, html_text_opt_6_alternatives_multi_otcenas_uvod},
	}},
};

Element optionsXml() {
	Element result{XML_OPTIONS, {}, {}, ""};
	for (const auto& group : optionGroups) {
		Element element{group.element, {
			{"Value", std::to_string(_global_opt[group.index])},
			{"Name", group.parameter}, {"ForceName", group.forceName},
			{"Text", localized(group.labels)},
		}, {}, ""};
		for (const auto& option : group.options) {
			element.children.push_back({option.element, {
				{"Id", std::to_string(option.mask)}, {"ForceName", option.forceName},
				{"Text", option.label()},
			}, {}, std::to_string(isGlobalOption(group.index, option.mask))});
		}
		if (group.index == OPT_3_SPOLOCNA_CAST && _global_opt[group.index] <= MODL_SPOL_CAST_NEBRAT) {
			element.text = nazov_spolc(_global_opt[group.index]);
		}
		result.children.push_back(std::move(element));
	}
	return result;
}

bool hasLabel(const std::string& label) {
	// Empty alternatives (" / ") and untranslated placeholders also occur in the
	// legacy dictionaries. They must remain in Options, but are not menu entries.
	return label.find_first_not_of(" /\t\r\n") != std::string::npos
		&& label.find("_text") == std::string::npos;
}

std::string menuLabel(const std::string& label) {
	// Web-form captions sometimes end with a colon or padding. Native controls
	// supply their own layout, as the existing Android settings renderer does.
	const auto begin = label.find_first_not_of(" \t\r\n");
	const auto end = label.find_last_not_of(" :\t\r\n");
	if (begin == std::string::npos || end == std::string::npos || end < begin) return "";
	return mystr_first_upper(label.substr(begin, end - begin + 1).c_str());
}

Element group(const char* key, const std::string& label, std::initializer_list<Element> children, bool applicable = true) {
	if (!applicable) return {};
	Element result{"MenuGroup", {{"Key", key}}, {}, ""};
	if (hasLabel(label)) result.attributes.emplace_back("Label", menuLabel(label));
	for (const auto& child : children) {
		if (!child.name.empty()) result.children.push_back(child);
	}
	return result.children.empty() ? Element{} : result;
}

Element item(const char* key, const std::string& label, const char* control,
	Attributes attributes, std::initializer_list<Element> children = {}) {
	if (!hasLabel(label)) return {};
	Element result{"MenuItem", {
		{"Key", key}, {"Label", menuLabel(label)}, {"Control", control},
	}, {}, ""};
	result.attributes.insert(result.attributes.end(), attributes.begin(), attributes.end());
	for (const auto& child : children) {
		if (!child.name.empty()) result.children.push_back(child);
	}
	return result;
}

Element toggle(const char* key, const char* optionRef, bool applicable = true) {
	if (!applicable) return {};
	for (const auto& group : optionGroups) {
		for (const auto& option : group.options) {
			if (std::string(option.element) == optionRef) {
				return item(key, option.label(), "toggle", {{"OptionRef", optionRef}});
			}
		}
	}
	return {}; // A catalog reference must resolve; checked by the XML contract test.
}

// Native/group labels can fall back to English. Option labels deliberately do
// not: an empty translation often identifies a language-specific option.
std::string menuText(const char* const* labels) {
	const std::string label = localized(labels);
	return hasLabel(label) ? label : labels[JAZYK_EN];
}

Element menuXml() {
	// The Czech edition uses its own hymn selection. Two-year readings are (intended to be) implemented for Slovak only; alternative readings are specific to Czech only (not even for CZ OP).
	const bool czechHymns = _global_jazyk == JAZYK_CZ;
	return {"Menu", {{"Version", "1"}}, {
		group("general", menuText(text_menu_group_jazyk[MENU_0_GENERAL]), {
			item("language", menuText(html_text_Jazyk), "choice", {{"Parameter", STR_JAZYK}, {"ValuesRef", XML_SUPPORTED_LANGUAGES}, {"Handler", "language.select"}}, {
				group("language.interface", "", {
					item("language.use-for-interface", menuText(menu_text_language_use_for_interface), "toggle", {{"Handler", "language.use-for-interface"}}),
				}),
			}),
			item("calendar", menuText(text_menu_group_jazyk[MENU_4_CALENDAR]), "choice", {{"Parameter", STR_KALENDAR}, {"ValuesRef", XML_LIT_CALENDAR_VALUES}}, {
				group("calendar.options", menuText(text_menu_group_jazyk[MENU_4_CALENDAR]), {
					toggle("calendar.epiphany-sunday", XML_BIT_OPT_0_ZJAVENIE_PANA_NEDELA),
					toggle("calendar.ascension-sunday", XML_BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA),
					toggle("calendar.corpus-christi-sunday", XML_BIT_OPT_0_TELAKRVI_NEDELA),
					toggle("calendar.highlight-national", XML_BIT_OPT_2_SHOW_DEFAULT_CALENDAR),
				}),
			}),
			item("general.online-mode", menuText(menu_text_mode), "choice", {{"Handler", "general.online-mode"}}),
		}),
		group("device", menuText(text_menu_group_jazyk[MENU_1_DEVICE]), {
			item("device.eink", menuText(menu_text_device_eink), "toggle", {{"Handler", "device.eink"}}),
			item("device.volume-paging", menuText(menu_text_volume_buttons), "toggle", {{"Handler", "device.volume-paging"}}),
			item("device.keep-awake", menuText(menu_text_do_not_dim_screen), "toggle", {{"Handler", "device.keep-awake"}}),
			item("device.do-not-disturb", menuText(menu_text_do_not_disturb), "toggle", {{"Handler", "device.do-not-disturb"}}),
			item("device.lock-zoom", menuText(menu_text_lock_font_size), "toggle", {{"Handler", "device.lock-zoom"}}),
		}),
		group("appearance", menuText(text_menu_group_jazyk[MENU_2_LOOK]), {
			group("appearance.font-margins", menuText(menu_text_font_and_margins),{
				item("appearance.font", menuText(html_text_font_name), "font", {
					{"Parameter", STR_FONT_NAME},
					{"Default", ""},
					{"ResetValue", ""},
					{"Handler", "appearance.font"},
				}),
				item("appearance.font-size", menuText(html_text_font_size), "number", {
					{"Parameter", STR_FONT_SIZE_PT},
					{"Default", "12"},
					{"ResetValue", "12"},
					{"Min", "4"},
					{"Max", "60"},
					{"Handler", "appearance.font-size"},
				}),
				toggle("appearance.normal-weight", XML_BIT_OPT_0_FONT_NORMAL),
				item("appearance.margin", menuText(menu_text_appearance_margin), "number", {
					{"Parameter", STR_STYLE_MARGIN},
					{"Default", std::to_string(DEF_STYLE_MARGIN)},
					{"ResetValue", ""},
					{"Min", "1"},
					{"Max", "200"},
				}),
				item("appearance.line-height", menuText(menu_text_appearance_line_height), "number", {
					{"Parameter", STR_LINE_HEIGHT_PERC},
					{"Default", std::to_string(DEF_LINE_HEIGHT_PERC)},
					{"ResetValue", ""},
					{"Min", "1"},
					{"Max", "500"},
				}),
			}),
			group("appearance.colors", menuText(menu_text_colors),{
				toggle("appearance.night-mode", XML_BIT_OPT_2_NOCNY_REZIM),
				item("appearance.background-day", menuText(menu_text_appearance_background_day), "color", {
					{"Parameter", STR_THEME_LIGHT_BACKGROUND_COLOR},
					{"Default", ""},
					{"ResetValue", ""},
				}),
				item("appearance.background-night", menuText(menu_text_appearance_background_night), "color", {
					{"Parameter", STR_THEME_DARK_BACKGROUND_COLOR},
					{"Default", ""},
					{"ResetValue", ""},
				}),
			}),
			group("appearance.navigation", menuText(menu_text_navigation),{
				item("reading.navigation", menuText(menu_text_reading_navigation), "choice",{ { "Handler", "reading.navigation" } },{
					group("reading.arrow-options", menuText(html_text_opt_0_transparent_nav),{
						toggle("reading.arrows-left", XML_BIT_OPT_0_TRANSPARENT_NAV_LEFT),
						toggle("reading.down-arrow-only", XML_BIT_OPT_0_TRANSPARENT_NAV_DOWN_ONLY),
					}),
				}),
			}),
			group("appearance.buttons", menuText(menu_text_buttons),{
				toggle("appearance.prayer-buttons", XML_BIT_OPT_2_PRAYER_BUTTONS),
				toggle("appearance.date-buttons-below", XML_BIT_OPT_0_BUTTONS_ORDER),
				toggle("appearance.rounded-buttons", XML_BIT_OPT_2_ROUNDED_CORNERS),
				toggle("appearance.first-vespers", XML_BIT_OPT_2_BUTTON_PRVE_VESPERY),
				toggle("appearance.compact-buttons", XML_BIT_OPT_2_BUTTONY_USPORNE),
			}),
			group("appearance.other", menuText(menu_text_appearance_other),{
				toggle("appearance.printed-line-breaks", XML_BIT_OPT_2_TEXT_WRAP),
				toggle("appearance.iso-dates", XML_BIT_OPT_2_ISO_DATUM),
			}),
		}),
		group("prayers", menuText(text_menu_group_jazyk[MENU_3_TEXT_CONTENT]), {
			toggle("prayers.inline-options", XML_BIT_OPT_2_ROZNE_MOZNOSTI),
			group("prayers.presentation", menuText(menu_text_prayers_presentation), {
				toggle("prayers.verse-numbers", XML_BIT_OPT_0_VERSE),
				toggle("prayers.references", XML_BIT_OPT_0_REFERENCIE),
				toggle("prayers.references-bible-com", XML_BIT_OPT_0_REF_BIBLE_COM),
				toggle("prayers.psalm-omissions", XML_BIT_OPT_0_ZALMY_FULL_TEXT),
				toggle("prayers.conditional-italics", XML_BIT_OPT_0_ITALICS_CONDITIONAL),
				toggle("prayers.notes", XML_BIT_OPT_0_FOOTNOTES),
				toggle("prayers.printed-edition", XML_BIT_OPT_0_PRINTED_EDITION),
				toggle("prayers.hide-saint-description", XML_BIT_OPT_1_SKRY_POPIS),
				toggle("prayers.common-description", XML_BIT_OPT_1_ZOBRAZ_SPOL_CAST),
				toggle("prayers.mass-readings", XML_BIT_OPT_0_CITANIA),
			}),
			group("prayers.parts", menuText(html_text_opt_1_nemenne_sucasti), {
				toggle("prayers.rubrics", XML_BIT_OPT_1_RUBRIKY),
				toggle("prayers.gospel-canticles", XML_BIT_OPT_1_CHVALOSPEVY),
				toggle("prayers.glory", XML_BIT_OPT_1_SLAVA_OTCU),
				toggle("prayers.our-father", XML_BIT_OPT_1_OTCENAS),
				toggle("prayers.our-father-introduction", XML_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD),
				toggle("prayers.full-responses", XML_BIT_OPT_1_PLNE_RESP),
				toggle("prayers.te-deum", XML_BIT_OPT_1_TEDEUM),
				toggle("prayers.conclusions", XML_BIT_OPT_1_ZAVER),
				toggle("prayers.marian-antiphons", XML_BIT_OPT_1_KOMPL_MARIA_ANT),
			}),
			group("prayers.celebration", menuText(menu_text_prayers_celebration),{ 
				toggle("prayers.memorial-common", XML_BIT_OPT_1_SPOMIENKA_SPOL_CAST),
				toggle("prayers.raise-rank", XML_BIT_OPT_1_OVERRIDE_STUP_SLAV),
				toggle("prayers.as-solemnity", XML_BIT_OPT_1_STUP_SVIATOK_SLAVNOST),
				item("prayers.common", menuText(html_text_spol_casti_vziat_zo), "choice",{
					{ "OptionRef", XML_OPT_3_SPOLOCNA_CAST },
					{ "ValuesRef", XML_LIT_COMMUNIA_VALUES },
					{ "ValueAttribute", "Id" },
				}),
			}),
			group("prayers.other", menuText(html_text_opt_1_dalsie_prepinace),{
				toggle("prayers.repeat-response", XML_BIT_OPT_1_PROSBY_ZVOLANIE),
				toggle("prayers.short-evening-intercessions", XML_BIT_OPT_1_VESP_KRATSIE_PROSBY),
				toggle("prayers.vigil", XML_BIT_OPT_1_PC_VIGILIA),
				toggle("prayers.ordained-conclusion", XML_BIT_OPT_5_ZAVER_KNAZ_DIAKON),
			}),
			toggle("prayers.alternatives-inline", XML_BIT_OPT_2_ALTERNATIVES),
			group("prayers.alternatives", menuText(html_text_opt_2_alternatives), {
				toggle("prayers.alternatives.cz-hymn-selection", XML_BIT_OPT_5_CZ_HYMNY_VYBER, czechHymns),
				toggle("prayers.alternatives.week-34-hymns", XML_BIT_OPT_5_OCR_34_HYMNS),
				group("prayers.alternatives.invitatory", menuText(nazov_Modlitby_jazyk[MODL_INVITATORIUM]),{
					toggle("prayers.alternatives.invitatory.psalm-95", XML_BIT_OPT_1_ZALM95),
					toggle("prayers.alternatives.invitatory.antiphon", XML_BIT_OPT_5_INVITAT_ANT_WRAP_ONLY),
				}),
				group("prayers.alternatives.readings", menuText(nazov_Modlitby_jazyk[MODL_POSV_CITANIE]),{
					toggle("prayers.alternatives.readings.two-year-cycle", XML_BIT_OPT_0_USE_TWO_YEARS_CYCLE, _global_jazyk == JAZYK_SK), // ToDo also for other languages
					toggle("prayers.alternatives.readings.invert-cycle", XML_BIT_OPT_0_TWO_YEARS_CYCLE_INVERT, _global_jazyk == JAZYK_SK), // ToDo also for other languages
					toggle("prayers.alternatives.readings.cz-alternatives", XML_BIT_OPT_0_ALTERNATIVE_READINGS, _global_jazyk == JAZYK_CZ),
					toggle("prayers.alternatives.readings.hymn-alternatives", XML_BIT_OPT_5_HYMNUS_PC, !czechHymns),
				}),
				group("prayers.alternatives.daytime", menuText(html_text_modlitba_cez_den),{
					toggle("prayers.alternatives.daytime.supplementary", XML_BIT_OPT_1_MCD_DOPLNKOVA),
					toggle("prayers.alternatives.daytime.three-weeks", XML_BIT_OPT_1_MCD_ZALTAR_TRI),
					toggle("prayers.alternatives.daytime.psalm-122", XML_BIT_OPT_5_DOPLNK_PSALM_122_129),
					toggle("prayers.alternatives.daytime.psalm-126", XML_BIT_OPT_5_DOPLNK_PSALM_126_129),
					toggle("prayers.alternatives.daytime.psalm-127", XML_BIT_OPT_5_DOPLNK_PSALM_127_131),
					toggle("prayers.alternatives.daytime.midmorning-hymn", XML_BIT_OPT_5_HYMNUS_MCD_PREDPOL, !czechHymns),
					toggle("prayers.alternatives.daytime.midday-hymn", XML_BIT_OPT_5_HYMNUS_MCD_NAPOL, !czechHymns),
					toggle("prayers.alternatives.daytime.midafternoon-hymn", XML_BIT_OPT_5_HYMNUS_MCD_POPOL, !czechHymns),
				}),
				group("prayers.alternatives.first-vespers", menuText(nazov_Modlitby_jazyk[MODL_PRVE_VESPERY]),{
					toggle("alternatives.first-vespers-hymn", XML_BIT_OPT_5_HYMNUS_1VESP, !czechHymns),
				}, !czechHymns),
				toggle("prayers.alternatives.ash-wednesday", XML_BIT_OPT_5_POPOL_STREDA_PSALMODIA),
				toggle("prayers.alternatives.holy-thursday", XML_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA),
				toggle("prayers.alternatives.office-dead-psalm", XML_BIT_OPT_5_OFF_DEF_PSALM_146_150),
				toggle("prayers.alternatives.compline-hymn", XML_BIT_OPT_5_HYMNUS_KOMPL, !czechHymns),
				toggle("prayers.alternatives.easter-readings-hymn", XML_BIT_OPT_5_HYMNUS_VN_PC, !czechHymns),
				toggle("prayers.alternatives.easter-morning-hymn", XML_BIT_OPT_5_HYMNUS_VN_RCH, !czechHymns),
				toggle("prayers.alternatives.easter-evening-hymn", XML_BIT_OPT_5_HYMNUS_VN_VESP, !czechHymns),
				toggle("prayers.alternatives.octave-compline", XML_BIT_OPT_5_KOMPLETORIUM_OKTAVA, !czechHymns),
				toggle("prayers.alternatives.lent-fifth-week", XML_BIT_OPT_5_LENT_5_HYMNS, !czechHymns),
			}),
		}),
		group("speech", menuText(text_menu_group_jazyk[MENU_5_TTS]), {
			item("speech.rate", menuText(menu_text_speech_rate), "number", {{"Handler", "speech.rate"}}),
			item("speech.psalm-pauses", menuText(menu_text_speech_psalm_pauses), "toggle", {{"Handler", "speech.psalm-pauses"}}),
			item("speech.help", menuText(menu_text_speech_help), "action", {{"Handler", "speech.help"}}),
		}),
	}, ""};
}

} // namespace

void xml_export_options_and_menu() {
	std::string xml;
	appendXml(xml, menuXml());
	appendXml(xml, optionsXml());
	// Export_to_string() counts a single write in a short int. The combined
	// catalog can exceed that even though individual labels are small.
	constexpr int chunkSize = 4096;
	for (std::size_t offset = 0; offset < xml.size(); offset += chunkSize) {
		Export("%.*s", chunkSize, xml.c_str() + offset);
	}
}
