// Rendering selected sections of the shared prayer text files.
#include "prayer-renderer.h"
#include "template-reader.h"
#include "prayer-markup.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include "breviar.h"
#include "mystring.h"
#include "myconf.h"
#include "mydefs.h"
#include "myexpt.h"
#include "mylog.h"
#include "myhpage.h"
#include "prayer-text.h"

#define DetailLog emptyLog

void export_div_to_continue_tts_voice_output(short int export_comment_begin) {
	// used both in includeFile() and interpretParameter()
	Export(HTML_P_END "\n"); // end of first verse of psalm/canticle which started <p class="verse...">
	Export(HTML_DIV_END "\n"); // end of <div class="psalm"> which is in each psalm/canticle
	Export(HTML_DIV_END "\n"); // end of HTML_DIV_RUBRIC added above
	Export("<" HTML_DIV_PSALM ">" "\n" HTML_P_VERSE_CONT "\n"); // synthetic begin of psalm + verse
	if (export_comment_begin == ANO) {
		Export(HTML_COMMENT_BEGIN);
	}
}// export_div_to_continue_tts_voice_output()

void export_tts_pause(short int tts_pause_type) {
	DetailLog("exporting TTS pause...\n");

	Export("\n");

	if (tts_pause_type == TTS_PAUSE) {
		Export("<" HTML_SPAN_TTS_PAUSE ">");
	}
	else if (tts_pause_type == TTS_PAUSE_SHORT) {
		Export("<" HTML_SPAN_TTS_PAUSE_SHORT ">");
	}
	else if (tts_pause_type == TTS_PAUSE_LONG) {
		Export("<" HTML_SPAN_TTS_PAUSE_LONG ">");
	}

	Export(HTML_SPAN_END "\n");
}// export_tts_pause()

namespace {

// The prayer records have different types but share the three psalm fields.
template<class Prayer>
const char* psalmForAntiphon(const Prayer& prayer, const std::string& part,
                            const char* second = PARAM_ANTIFONA2,
                            const char* third = PARAM_ANTIFONA3) {
    if (part == PARAM_ANTIFONA1) return prayer.zalm1.anchor;
    if (part == second) return prayer.zalm2.anchor;
    if (part == third) return prayer.zalm3.anchor;
    return nullptr;
}

const char* psalmForAntiphon(const std::string& part) {
    switch (_global_modlitba) {
    case MODL_RANNE_CHVALY: return psalmForAntiphon(_global_modl_ranne_chvaly, part, PARAM_ANTRCHVAL);
    case MODL_CEZ_DEN_9: return psalmForAntiphon(_global_modl_cez_den_9, part);
    case MODL_CEZ_DEN_12: return psalmForAntiphon(_global_modl_cez_den_12, part);
    case MODL_CEZ_DEN_3: return psalmForAntiphon(_global_modl_cez_den_3, part);
    case MODL_VESPERY: return psalmForAntiphon(_global_modl_vespery, part, PARAM_ANTIFONA2, PARAM_ANTVCHVAL);
    case MODL_PRVE_VESPERY: return psalmForAntiphon(_global_modl_prve_vespery, part, PARAM_ANTIFONA2, PARAM_ANTVCHVAL);
    case MODL_POSV_CITANIE: return psalmForAntiphon(_global_modl_posv_citanie, part);
    case MODL_KOMPLETORIUM:
        if (part == PARAM_ANTIFONA1k) return _global_modl_kompletorium.zalm1.anchor;
        if (part == PARAM_ANTIFONA2k) return _global_modl_kompletorium.zalm2.anchor;
        break;
    case MODL_PRVE_KOMPLETORIUM:
        if (part == PARAM_ANTIFONA1k) return _global_modl_prve_kompletorium.zalm1.anchor;
        if (part == PARAM_ANTIFONA2k) return _global_modl_prve_kompletorium.zalm2.anchor;
        break;
    default: break; // The invitatory psalm is written directly in its template.
    }
    return nullptr;
}

void renderCross(prayer::RenderState& state, const std::string& part,
                 const std::string& anchor, const std::string& argument) {
    const bool antiphon = part == PARAM_ANTIFONA1 || part == PARAM_ANTIFONA2 || part == PARAM_ANTIFONA3
        || part == PARAM_ANTRCHVAL || part == PARAM_ANTVCHVAL
        || part == PARAM_ANTIFONA1x || part == PARAM_ANTIFONA3x;
    if (antiphon && !argument.empty()) state.crossAnchor = argument;
    if (part == PARAM_ANTIFONA1) state.invitatoryCross = true;
#if defined(EXPORT_HTML_SPECIALS)
    Export("[%s:%s|crossAnchor=%s]", PARAM_KRIZIK, anchor.c_str(), state.crossAnchor.c_str());
#endif
    if (antiphon) {
        // Only the opening antiphon carries the cross; the invitatory repeats it.
        if (state.antiphonCount % 2 == 0
            || (state.antiphonCount > 1 && _global_modlitba == MODL_INVITATORIUM)) return;
        const char* psalm = psalmForAntiphon(part);
        if (psalm && state.crossAnchor != psalm) return;
    } else {
        const bool psalm = part == PARAM_ZALM1 || part == PARAM_ZALM2 || part == PARAM_ZALM3
            || part == PARAM_RCHVALOSPEV || part == PARAM_VCHVALOSPEV;
        if (!psalm || anchor != state.crossAnchor) return;
    }
    Export(HTML_COMMENT_END);
    if (antiphon) ExportNonbreakingSpace();
    Export("<" HTML_SPAN_RED ">" STR_CROSS HTML_SPAN_END);
    if (!antiphon) ExportNonbreakingSpace();
    Export(HTML_COMMENT_BEGIN);

    if (!isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) return;
    Export(HTML_COMMENT_END "\n");
    if (antiphon) {
        // Hide the repeated opening of the psalm until its corresponding cross.
        Export(_global_jazyk == JAZYK_HU ? HTML_DIV_END : HTML_P_END);
        export_tts_pause();
        Export(HTML_DIV_RUBRIC "\n");
        Export(_global_jazyk == JAZYK_HU ? HTML_DIV_BEGIN : HTML_P_BEGIN);
        Export(HTML_COMMENT_BEGIN);
    } else {
        export_div_to_continue_tts_voice_output();
    }
}

void renderPsalmChoice(short type, const char* part, const std::string& name) {
    struct Choice {
        const char* marker;
        unsigned long long bit;
        bool available;
        const char* normalLabel;
        const char* alternativeLabel;
        const char* normalAnchor;
        const char* alternativeAnchor;
    };
    const int language = _global_jazyk;
    const Choice choices[] = {
        {PARAM_DOPLNK_PSALM_122_129, BIT_OPT_5_DOPLNK_PSALM_122_129, !!je_alternativa_doplnkova_psalmodia_z122_129(_global_modlitba),
         html_text_opt_5_DPsalmZ122_NORMAL[language], html_text_opt_5_DPsalmZ122_129[language], PARAM_ZALM122, PARAM_ZALM129},
        {PARAM_DOPLNK_PSALM_126_129, BIT_OPT_5_DOPLNK_PSALM_126_129, !!je_alternativa_doplnkova_psalmodia_z126_129(_global_modlitba),
         html_text_opt_5_DPsalmZ126_NORMAL[language], html_text_opt_5_DPsalmZ126_129[language], PARAM_ZALM126, PARAM_ZALM129},
        {PARAM_DOPLNK_PSALM_127_131, BIT_OPT_5_DOPLNK_PSALM_127_131, !!je_alternativa_doplnkova_psalmodia_z127_131(_global_modlitba),
         html_text_opt_5_DPsalmZ127_NORMAL[language], html_text_opt_5_DPsalmZ127_131[language], PARAM_ZALM127, PARAM_ZALM131},
        {PARAM_OFF_DEF_PSALM_146_150, BIT_OPT_5_OFF_DEF_PSALM_146_150, !!je_alternativa_off_def_z146_150(_global_modlitba),
         html_text_opt_5_OffDefZ146_150_NORMAL[language], html_text_opt_5_OffDefZ146_150[language], PARAM_ZALM146, PARAM_ZALM150},
    };
    for (const auto& choice : choices) {
        if (name != choice.marker) continue;
        if (!choice.available || !isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)
            || !isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)) {
            if (type != PRM_XML) Export("[skipping %s]", part);
            return;
        }
        // Adapt the existing link builder's mutable-buffer interface in one place.
        char show[MAX_STR], hide[MAX_STR], anchor[SMALL];
        mystrcpy(show, choice.normalLabel, sizeof(show));
        mystrcpy(hide, choice.alternativeLabel, sizeof(hide));
        mystrcpy(anchor, isGlobalOption(OPT_5_ALTERNATIVES, choice.bit)
            ? choice.normalAnchor : choice.alternativeAnchor, sizeof(anchor));
        char css[] = HTML_SPAN_RED_SMALL, linkClass[] = HTML_CLASS_QUIET;
        char before[] = HTML_P_BEGIN, after[] = "", end[] = HTML_SPAN_END;
        Export("%s:begin" HTML_COMMENT_END, part);
        _export_link_show_hide(OPT_5_ALTERNATIVES, choice.bit, show, hide, css, linkClass, before, after, anchor, end);
        Export(HTML_COMMENT_BEGIN "%s:end", part);
        return;
    }
}

void renderEnding(prayer::RenderState& state, const std::string& part,
                  const std::string& argument) {
    const bool easterReading = (part == PARAM_CITANIE1 || part == PARAM_CITANIE2)
        && _global_den.denvr == VELKONOCNA_NEDELA && _global_modlitba == MODL_POSV_CITANIE;
    if (part != PARAM_MODLITBA && part != PARAM_MODL_SPOMPRIVILEG && !easterReading) return;
    if (!argument.empty()) state.ending = argument;
    // In a privileged-day commemoration the conclusion follows its collect.
    if (part == PARAM_MODLITBA && je_modl_spomprivileg
        && (_global_modlitba == MODL_RANNE_CHVALY || _global_modlitba == MODL_VESPERY)) return;

    const bool shortForm = je_modlitba_cez_den(_global_modlitba)
        || je_kompletorium12(_global_modlitba) || easterReading;
    const int language = _global_jazyk;
    const auto& name = state.ending;
    const char* text = nullptr;
    if (name == PARAM_ZAKONCENIE_SKRZE || name == PARAM_ZAKONCENIE_SKRZE_MALE)
        text = shortForm ? text_ZAKONCENIE_SKRZE_kratke[language] : text_ZAKONCENIE_SKRZE_dlhe[language];
    else if (name == PARAM_ZAKONCENIE_LEBO_TY || name == PARAM_ZAKONCENIE_LEBO_TY_MALE)
        text = shortForm ? text_ZAKONCENIE_LEBO_TY_kratke[language] : text_ZAKONCENIE_LEBO_TY_dlhe[language];
    else if (name == PARAM_ZAKONCENIE_LEBO_ON || name == PARAM_ZAKONCENIE_LEBO_ON_MALE)
        text = shortForm ? text_ZAKONCENIE_LEBO_ON_kratke[language] : text_ZAKONCENIE_LEBO_ON_dlhe[language];
    else if (argument == PARAM_ZAKONCENIE_ON_JE && language == JAZYK_SK)
        text = shortForm ? text_SK_ZAKONCENIE_ON_JE_kratke : text_SK_ZAKONCENIE_ON_JE_dlhe;
    else if ((argument == PARAM_ZAKONCENIE_KTORY_JE || name == PARAM_ZAKONCENIE_KTORY_JE_MALE) && language == JAZYK_SK)
        text = shortForm ? text_SK_ZAKONCENIE_KTORY_JE_kratke : text_SK_ZAKONCENIE_KTORY_JE_dlhe;
    else if ((argument == PARAM_ZAKONCENIE_KTORY_JE || name == PARAM_ZAKONCENIE_KTORY_JE_MALE) && language == JAZYK_IS)
        text = shortForm ? text_IS_ZAKONCENIE_KTORY_JE_kratke : text_IS_ZAKONCENIE_KTORY_JE_dlhe;
    else if (argument == PARAM_ZAKONCENIE_KTORY_ZIJES && language == JAZYK_IS)
        text = shortForm ? text_IS_ZAKONCENIE_KTORY_ZIJES_kratke : text_IS_ZAKONCENIE_KTORY_ZIJES_dlhe;
    else if (name == PARAM_ZAKONCENIE_O_TO_TA_PROSIME) text = text_ZAKONCENIE_O_TO_TA_PROSIME[language];
    if (!text) return; // Unknown endings used to read an uninitialized buffer.

    const bool lowercase = name == PARAM_ZAKONCENIE_SKRZE_MALE || name == PARAM_ZAKONCENIE_LEBO_TY_MALE
        || name == PARAM_ZAKONCENIE_LEBO_ON_MALE || name == PARAM_ZAKONCENIE_KTORY_JE_MALE;
    const std::string ending = lowercase ? mystr_first_lower(text) : std::string(text);
    Export("%s--> %s" HTML_COMMENT_BEGIN "%s", name.c_str(), convert_nonbreaking_spaces(ending.c_str()), name.c_str());
}

// Section conditions are separate from inline captures. Anchors are aliases, not
// a nesting tree. Conditional passages keep their own visibility state.
class SectionVisibility {
public:
    bool visible() const { return hidden_.empty(); }
    void boundary(const prayer::Marker& marker) {
        const auto& condition = marker.argument;
        bool hide;
        if (condition == PARAM_HIDE_FOR_VOICE_OUTPUT) hide = isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT);
        else if (condition == PARAM_ALELUJA_VO_VELKONOCNOM) hide = !je_velka_noc;
        else if (condition == PARAM_ALELUJA_NIE_V_POSTE) hide = je_post;
        else if (condition == PARAM_PLNE_RESP || condition == PARAM_PLNE_RESP_BODKA)
            hide = !useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP);
        else if (condition == PARAM_NIE_PLNE_RESP) hide = useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP);
        else if (condition == PARAM_ZVOLANIE) hide = !useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PROSBY_ZVOLANIE);
        else if (condition == PARAM_RUBRIKA)
            hide = isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_RUBRIKY) && !isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT);
        else if (condition == PARAM_PSALMODIA_MYSLIENKA || condition == PARAM_PSALMODIA_NADPIS)
            hide = isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT);
        else return;
        if (!hide) return;
        if (marker.name == INCLUDE_BEGIN) hidden_.push_back(condition);
        else if (marker.name == INCLUDE_END) {
            const auto found = std::find(hidden_.rbegin(), hidden_.rend(), condition);
            if (found != hidden_.rend()) hidden_.erase(std::next(found).base());
            if (condition == PARAM_PLNE_RESP_BODKA && visible()) Export("-->.<!--");
        }
    }
private:
    std::vector<std::string> hidden_;
};

} // namespace


prayer::SectionResult prayer::renderSection(RenderState& state, short type, short prayer, const char* part,
                                           const char* path, const char* anchor, bool reportErrors) {
    Log("renderSection(%d, %d, %s, %s, %s)\n", type, prayer, part, path, anchor);
    if (state.skipDepth > 0 || state.skipEasterReading) return SectionResult::Skipped;
    state.invitatoryCross = false;
    TemplateReader reader(path, "r");
    if (!reader.isOpen()) {
        if (reportErrors) {
#if defined(EXPORT_HTML_FILENAME_ANCHOR)
            Export("file `%s' not found (anchor `%s')", path, anchor);
#elif defined(EXPORT_HTML_FILENAME)
            Export("file `%s' not found", path);
#else
            Export("file not found");
#endif
        }
        return SectionResult::FileNotFound;
    }
    if (reportErrors) {
#if defined(EXPORT_HTML_FILENAME_ANCHOR)
        Export("(file `%s', anchor `%s')", path, anchor);
#elif defined(EXPORT_HTML_FILENAME)
        Export("(file `%s')", path);
#elif defined(EXPORT_HTML_ANCHOR)
        Export("(anchor `%s')", anchor);
#endif
    }

    bool selected = false;
    bool found = false;
    SectionVisibility visibility;
    InlineMarkup markup(MarkupStyle::Section);
    Token token;
    while (reader.next(token)) {
        const bool visible = selected && visibility.visible();
        if (token.kind == Token::Kind::Character) {
            markup.character(token.character, visible);
        } else if (token.kind == Token::Kind::Recovery) {
            markup.recovery(token.text, visible);
        } else {
            const Marker marker(token.text);
            if (equalsi(marker.argument.c_str(), anchor)) {
                if (marker.name == INCLUDE_BEGIN) selected = found = true;
                else if (marker.name == INCLUDE_END) {
                    selected = false;
                    // Close the selected text and reopen the template's comment.
                    Export("--><!--");
                }
                continue;
            }
            if (!selected) continue;
            if (marker.name == INCLUDE_BEGIN || marker.name == INCLUDE_END) {
                visibility.boundary(marker);
                continue;
            }
            if (markup.marker(marker, visible) || !markup.visible(visible)) continue;
            const auto& name = marker.name;
            const char* argument = marker.argument.c_str();
            if (name == PARAM_KRIZIK) renderCross(state, part, anchor, argument);
            else if (name == PARAM_ZAKONCENIE) renderEnding(state, part, argument);
            else if (name == PARAM_DOPLNK_PSALM_122_129 || name == PARAM_DOPLNK_PSALM_127_131
                || name == PARAM_DOPLNK_PSALM_126_129 || name == PARAM_OFF_DEF_PSALM_146_150)
                renderPsalmChoice(type, part, name);
            else if (name == PARAM_ZALOMENIE) {
#if !defined(IO_ANDROID) && !defined(__APPLE__)
                if (useWhenGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_TEXT_WRAP))
                    Export("zalomenie-->%s<!--zalomenie", argument);
#endif
            }
        }
    }
    if (reader.failed()) return SectionResult::ReadError;
    return found ? SectionResult::Rendered : SectionResult::SectionNotFound;
}

void includeFile(short type, short prayer, const char* part, const char* path, const char* anchor) {
    prayer::RenderState state;
    prayer::renderSection(state, type, prayer, part, path, anchor);
}
