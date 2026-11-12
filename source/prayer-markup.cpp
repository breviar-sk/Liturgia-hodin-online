// Inline markup shared by prayer templates and selected include sections.
#include "prayer-markup.h"
#include "bible-links.h"
#include "static-text.h"
#include "breviar.h"
#include "myconf.h"
#include "myexpt.h"
#include "mystring.h"
#include "prayer-text.h"
#include <utility>

namespace prayer {
namespace {

bool option(unsigned long long bit) { return useWhenGlobalOption(OPT_0_SPECIALNE, bit); }
bool voice() { return isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT); }

std::string spaces(const std::string& text) {
    std::string result;
    for (char c : text) {
        if (c == CHAR_NONBREAKING_THIN_SPACE || (c == CHAR_NONBREAKING_SPACE && _global_override_thin_nbsp))
            result += HTML_NONBREAKING_THIN_SPACE;
        else if (c == CHAR_NONBREAKING_SPACE) result += HTML_NONBREAKING_SPACE;
        else result += c;
    }
    return result;
}

std::string reference(const std::string& prefix, const std::string& label) {
    if (!isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) return spaces(label);
    bible::LinkSettings settings;
    settings.useBibleCom = isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REF_BIBLE_COM);
    settings.referenceBase = cfg_http_bible_references_default[_global_jazyk];
    settings.bibleComBase = cfg_http_bible_com_references_default[_global_jazyk];
    settings.bibleComEdition = cfg_bible_com_version_id_default[_global_jazyk];
#ifdef IO_ANDROID
    settings.removeDiacritics = true;
#endif
    const bible::BibleLinks links(bible::languageFromCode(skratka_jazyka[_global_jazyk]), settings);
    const auto result = links.link(prefix, label);
    if (result.url.empty()) return spaces(label);
    // URL component encoding belongs to providers; HTML escaping belongs here.
    return HTML_A_HREF_BEGIN "\"" + escapeHtmlAttribute(result.url) + "\" " HTML_TARGET_BLANK " " HTML_CLASS_QUIET ">"
        + spaces(label) + HTML_A_END;
}

std::string catechesis(const std::string& path, const std::string& label) {
    if (!isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) return spaces(label);
    std::string url = "/include/";
#ifdef INCLUDE_FOLDERS_NESTED
    url += std::string(postfix_jazyka[_global_jazyk]) + STR_PATH_SEPARATOR;
#endif
    return HTML_A_HREF_BEGIN "\"" + url + spaces(path)
        + "\" " HTML_TARGET_BLANK " " HTML_CLASS_QUIET ">" + spaces(label) + HTML_A_END;
}

// Keep the existing options/query builder for the Psalm 95 switch. Its temporary
// option change is scoped to constructing the link; rendering never changes it.
std::string psalm95(const std::string& label) {
    if (!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)) return "";
#ifndef BEHAVIOUR_WEB
    return spaces(label);
#else
    char parameters[MAX_STR] = {};
    char scratch[MAX_STR] = {};
    const auto saved = _global_opt[OPT_1_CASTI_MODLITBY];
    _global_opt[OPT_1_CASTI_MODLITBY] ^= BIT_OPT_1_ZALM95;
    if (_global_poradie_svaty > 0) {
        mysnprintf(parameters, HTML_AMPERSAND "%s=%d", STR_DALSI_SVATY, _global_poradie_svaty);
    }
    prilep_request_options(parameters, scratch);
    _global_opt[OPT_1_CASTI_MODLITBY] = saved;

    char query[MAX_STR] = {};
    if (query_type == PRM_DATUM) {
        mysnprintf(query, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d"
            HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%s", script_name,
            STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, _global_den.den, STR_MESIAC, _global_den.mesiac,
            STR_ROK, _global_den.rok, STR_MODLITBA, str_modlitby[_global_modlitba]);
    } else if (query_type == PRM_LIT_OBD) {
        mysnprintf(query, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d"
            HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%c" HTML_AMPERSAND "%s=%s", script_name,
            STR_QUERY_TYPE, STR_PRM_LIT_OBD, STR_DEN_V_TYZDNI, _global_den.denvt,
            STR_TYZDEN, _global_den.tyzden, STR_LIT_OBD, _global_den.litobd,
            STR_LIT_ROK, _global_den.litrok, STR_MODLITBA, str_modlitby[_global_modlitba]);
    }
    std::string result;
    if (query[0]) {
        result = HTML_P_BEGIN "\n<" HTML_SPAN_RED_SMALL ">\n" HTML_A_HREF_BEGIN "\""
            + std::string(query) + parameters + "#" PARAM_ZALM95 "\"";
    }
    // Standalone psalms have no day's psalmody to switch back to.
    if (result.empty()) return "";
    return result + " " HTML_CLASS_QUIET ">" + spaces(label) + HTML_A_END HTML_SPAN_END "\n";
#endif
}

} // namespace

bool InlineMarkup::visible(bool parentVisible) const {
    return parentVisible && (frames_.empty() || frames_.back().enabled);
}

void InlineMarkup::emit(const std::string& html) {
    if (!frames_.empty()) {
        auto& frame = frames_.back();
        switch (frame.kind) {
        case Kind::Reference: case Kind::FootnoteReference:
        case Kind::Catechesis: case Kind::Psalm95: case Kind::Link:
            frame.text += html;
            return;
        default: break;
        }
    }
    Export("%s", html.c_str());
}

void InlineMarkup::open(Kind kind, bool enabled, const std::string& argument,
                        const std::string& opening, const std::string& closing) {
    if (enabled) emit(opening);
    frames_.push_back({kind, enabled, argument, "", closing});
}

void InlineMarkup::close(Kind kind, bool parentVisible) {
    // Unmatched markers must not pop another construct or expose hidden text.
    if (frames_.empty() || frames_.back().kind != kind) return;
    const Frame frame = std::move(frames_.back());
    frames_.pop_back();
    if (!frame.enabled || !visible(parentVisible)) return;
    switch (kind) {
    case Kind::Reference: emit(reference(frame.argument, frame.text)); break;
    case Kind::FootnoteReference:
        emit(HTML_A_HREF_BEGIN "\"#fn" + spaces(frame.argument) + frame.text
            + "\" " HTML_CLASS_WITHOUT_BORDER ">" HTML_SUP_BEGIN + frame.text
            + HTML_SUP_END HTML_A_END);
        break;
    case Kind::Catechesis: emit(catechesis(frame.argument, frame.text)); break;
    case Kind::Psalm95: emit(psalm95(frame.text)); break;
    case Kind::Link: {
        const auto url = contentLink(frame.argument);
        emit(url.empty() ? frame.text : "<a href=\"" + escapeHtmlAttribute(url) + "\">" + frame.text + "</a>");
        break;
    }
    default: emit(frame.closing); break;
    }
}

void InlineMarkup::character(int character, bool parentVisible) {
    if (!visible(parentVisible)) return;
    const bool literal = html_.consume(character);
    if (!frames_.empty()) {
        const auto kind = frames_.back().kind;
        if (kind == Kind::Reference || kind == Kind::FootnoteReference
            || kind == Kind::Catechesis || kind == Kind::Psalm95 || kind == Kind::Link) {
            char bytes[8] = {};
            int length = 0;
            if (kind == Kind::Link && !literal && (character == CHAR_NONBREAKING_SPACE || character == CHAR_NONBREAKING_THIN_SPACE)) {
                frames_.back().text += spaces(std::string(1, static_cast<char>(character)));
                return;
            }
            AppendWchar(character, sizeof(bytes), bytes, &length);
            frames_.back().text.append(bytes, length);
            return;
        }
    }
    if (literal) ExportRawWchar(character);
    else ExportChar(character, voice());
}

void InlineMarkup::recovery(const std::string& text, bool parentVisible) {
    if (visible(parentVisible)) emit(spaces(text));
}

bool InlineMarkup::symbol(const std::string& name, bool enabled) {
    const bool pause = name == PARAM_PAUSE || name == PARAM_PAUSE_SHORT;
    const bool normal = name == PARAM_NORMAL_ASTERISK || name == PARAM_NORMAL_CROSS;
    const bool red = name == PARAM_RED_ASTERISK || name == PARAM_RED_CROSS || name == PARAM_RED_CROSS_TXT;
    const bool triangle = name == PARAM_RED_TRIANGLE || name == PARAM_RED_TRIANGLE_TXT;
    if (!pause && !normal && !red && !triangle) return false;
    if (!enabled) return true;
    if (pause || normal) {
        if (voice()) {
            if (pause && style_ == MarkupStyle::Section) emit("\n");
            emit((name == PARAM_PAUSE || name == PARAM_NORMAL_ASTERISK)
                ? "<" HTML_SPAN_TTS_PAUSE ">" HTML_SPAN_END
                : "<" HTML_SPAN_TTS_PAUSE_SHORT ">" HTML_SPAN_END);
            if (pause) emit("\n");
        } else if (normal) {
            emit(spaces("_") + (name == PARAM_NORMAL_ASTERISK ? STR_ASTERISK : STR_CROSS));
        }
        return true;
    }
    if (voice()) return true;
    const bool finalSymbol = triangle || (style_ == MarkupStyle::Template && name != PARAM_RED_ASTERISK);
    if (finalSymbol && isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU)) return true;
    if (finalSymbol) emit(spaces("_"));
    const char* css = style_ == MarkupStyle::Template ? HTML_SPAN_RED : HTML_SPAN_TTS_PAUSE_RED;
    const char* text = triangle ? PARAM_RED_TRIANGLE : name == PARAM_RED_ASTERISK ? PARAM_RED_ASTERISK : PARAM_RED_CROSS;
    emit("<" + std::string(css) + ">" + text + HTML_SPAN_END);
    return true;
}

bool InlineMarkup::tts(const Marker& marker, bool enabled) {
    if (marker.name != "TTS") return false;
    const auto& part = marker.argument;
    if (part != "SECTION" && part != "HEADING_BEGIN" && part != "HEADING_END") return false;
    if (!enabled) return true;
    if (part == "SECTION") {
        emit("tts:section:begin" HTML_COMMENT_END);
        // Included parts can start with a boundary inside an existing section.
        // Only outer templates add pauses; otherwise hidden/empty parts would
        // turn into sections containing nothing but a long pause.
        if (voice() && style_ == MarkupStyle::Template)
            emit("<" HTML_SPAN_TTS_PAUSE ">" HTML_SPAN_END "\n");
        emit("<" HTML_DIV_TTS_SECTION ">" HTML_DIV_END "\n");
        emit(HTML_COMMENT_BEGIN "tts:section:end");
    } else {
        emit(HTML_COMMENT_END);
        emit(part == "HEADING_BEGIN" ? "<" HTML_DIV_TTS_HEADING ">" : HTML_DIV_END);
        emit(HTML_COMMENT_BEGIN);
    }
    return true;
}

bool InlineMarkup::marker(const Marker& marker, bool parentVisible) {
    const auto& name = marker.name;
    const bool enabled = visible(parentVisible);
    if (tts(marker, enabled)) return true;
    if (symbol(name, enabled)) return true;

    struct Pair { const char* begin; const char* end; Kind kind; };
    static const Pair pairs[] = {
        {"link", "/link", Kind::Link},
        {PARAM_REFERENCIA_BEGIN, PARAM_REFERENCIA_END, Kind::Reference},
        {PARAM_FOOTNOTE_REF_BEGIN, PARAM_FOOTNOTE_REF_END, Kind::FootnoteReference},
        {PARAM_FOOTNOTE_BEGIN, PARAM_FOOTNOTE_END, Kind::Footnote},
        {PARAM_NOTE_BEGIN, PARAM_NOTE_END, Kind::Note},
        {PARAM_CISLO_VERSA_BEGIN, PARAM_CISLO_VERSA_END, Kind::Verse},
        {PARAM_ITALICS_COND_BEGIN, PARAM_ITALICS_COND_END, Kind::Italics},
        {PARAM_PSALM_FULL_TEXT_BEGIN, PARAM_PSALM_FULL_TEXT_END, Kind::FullText},
        {PARAM_PSALM_FULL_TEXT_SOFT_BEGIN, PARAM_PSALM_FULL_TEXT_SOFT_END, Kind::FullText},
        {PARAM_PSALM_FULL_TEXT_TXT_BEGIN, PARAM_PSALM_FULL_TEXT_TXT_END, Kind::FullText},
#ifdef BEHAVIOUR_WEB
        {PARAM_KATECHEZA_BEGIN, PARAM_KATECHEZA_END, Kind::Catechesis},
#endif
        {PARAM_LINK_ZALM95_BEGIN, PARAM_LINK_ZALM95_END, Kind::Psalm95},
    };
    for (const auto& pair : pairs) {
        if (name == pair.end) {
            close(pair.kind, parentVisible);
            return true;
        }
        if (name != pair.begin) continue;
        bool show = enabled;
        std::string opening, closing;
        switch (pair.kind) {
        case Kind::Verse:
            show = show && option(BIT_OPT_0_VERSE);
            opening = HTML_SUP_BEGIN; closing = HTML_SUP_END;
            break;
        case Kind::Italics:
            if (option(BIT_OPT_0_ITALICS_CONDITIONAL)) { opening = "<i>"; closing = "</i>"; }
            break;
        case Kind::FullText:
            show = show && option(BIT_OPT_0_ZALMY_FULL_TEXT);
            if (name == PARAM_PSALM_FULL_TEXT_BEGIN) { opening = "<" HTML_DIV_PSALM_INDENT ">"; closing = HTML_DIV_END; }
            if (name == PARAM_PSALM_FULL_TEXT_TXT_BEGIN) { opening = "<" HTML_SPAN_SMALL ">"; closing = HTML_SPAN_END; }
            break;
        case Kind::FootnoteReference: case Kind::Footnote: case Kind::Note:
            show = show && option(BIT_OPT_0_FOOTNOTES);
            if (pair.kind == Kind::Note) { opening = " <" HTML_SPAN_TEXTNOTE ">("; closing = ")" HTML_SPAN_END; }
            if (pair.kind == Kind::Footnote && !marker.argument.empty()) {
                opening = HTML_A_NAME_BEGIN "\"fn" + marker.argument + "\">" HTML_A_END
                    HTML_SUP_BEGIN + marker.argument + HTML_SUP_END + spaces("_");
            }
            break;
        default: break;
        }
        open(pair.kind, show, marker.argument, opening, closing);
        return true;
    }
    return false;
}

} // namespace prayer
