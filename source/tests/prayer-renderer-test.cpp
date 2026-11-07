// Characterization fixtures for the legacy renderer. Keep exact comments,
// spacing and TTS markup: they are part of the template/output contract.
#include "breviar.h"
#include "myexpt.h"
#include "prayer-renderer.h"
#include "prayer-markup.h"
#include "mystring.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>


static bool record;
static unsigned failures;

static void check(const std::string& name) {
    const std::string path = "tests/fixtures/rendered-" + name + ".htm";
    const std::string actual = getExportedString();
    if (record) {
        std::ofstream(path, std::ios::binary) << actual;
    } else {
        std::ifstream input(path, std::ios::binary);
        const std::string expected((std::istreambuf_iterator<char>(input)), {});
        if (!input || actual != expected) {
            std::cerr << "Rendering differs: " << name << '\n';
            std::ofstream(".test-build/actual-" + name + ".htm", std::ios::binary) << actual;
            ++failures;
        }
    }
    closeExport();
}

static void expect(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; ++failures; }
}

static std::string inlineText(const std::string& text) {
    prayer::InlineMarkup markup(prayer::MarkupStyle::Section);
    initExport();
    const char* cursor = text.c_str();
    while (*cursor) {
        if (*cursor == '{') {
            const char* end = std::strchr(cursor, '}');
            expect(end != nullptr, "Test input has unfinished marker");
            if (!end) break;
            markup.marker(prayer::Marker(std::string(cursor + 1, end)), true);
            cursor = end + 1;
        } else markup.character(DecodeWchar(&cursor), true);
    }
    const std::string result = getExportedString();
    closeExport();
    return result;
}

static void checkInlineState() {
    _global_opt[0] = BIT_OPT_0_REFERENCIE | BIT_OPT_0_FOOTNOTES;
    _global_opt[1] = 0;
    const auto reference = inlineText("{r}Jn 1, 1{/r}");
    expect(inlineText("{r}Jn 1, 1{/r} 6,3-11{/r}") == reference + " 6,3-11",
           "An unmatched closing reference repeated the previous citation");
    expect(inlineText("{full-text}hidden {r}Jn 1, 1{/r} hidden{/full-text}visible") == "visible",
           "A reference exposed text hidden by the full-text option");
    expect(inlineText("{full-text}{v}12{/v}hidden{/full-text}visible") == "visible",
           "A verse exposed text hidden by the full-text option");
    const auto note = inlineText("{fn:1}before {r}Jn 1, 1{/r} after{/fn}");
    expect(note.find("before " + reference + " after") != std::string::npos,
           "Footnote capture lost text around a nested reference");
    expect(inlineText("{fn}before {r}Jn 1, 1{/r} after{/fn}") == "before " + reference + " after",
           "An unnumbered footnote lost its text before a reference");
    const std::string longNote(1024, 'a');
    expect(inlineText("{fn}" + longNote + "{/fn}") == longNote, "Long footnote was truncated");
    _global_opt[0] = 0;
    expect(inlineText("{fn}hidden {r}Jn 1, 1{/r} hidden{/fn}visible") == "visible",
           "A reference exposed a disabled footnote");
    initExport();
    includeFile(PRM_DATUM, MODL_VESPERY, PARAM_ZALM1,
        "tests/fixtures/prayer-visibility.htm", "chosen");
    const std::string output = getExportedString();
    closeExport();
    expect(output.find("VISIBLE") != std::string::npos, "Selected section disappeared");
    expect(output.find("HIDDEN") == std::string::npos, "An alias or nested condition exposed hidden text");
}

static std::string section(prayer::RenderState& state, const char* part, const char* anchor) {
    initExport();
    prayer::renderSection(state, PRM_DATUM, _global_modlitba, part,
        "tests/fixtures/prayer-visibility.htm", anchor);
    const std::string result = getExportedString();
    closeExport();
    return result;
}

static void checkLiturgicalMarkers() {
    _global_modlitba = MODL_VESPERY;
    _global_opt[0] = _global_opt[1] = 0;
    prayer::RenderState state;
    state.antiphonCount = 1;
    mystrcpy(_global_modl_vespery.zalm1.anchor, "cross-psalm", sizeof(_global_modl_vespery.zalm1.anchor));
    expect(section(state, PARAM_ANTIFONA1, "cross-ant").find("†") != std::string::npos,
           "Opening antiphon lost its cross");
    expect(section(state, PARAM_ZALM1, "cross-psalm").find("†") != std::string::npos,
           "Cross anchor was not shared with the following psalm");
    state.antiphonCount = 2;
    expect(section(state, PARAM_ANTIFONA1, "cross-ant").find("†") == std::string::npos,
           "Repeated antiphon kept its cross");
    state.antiphonCount = 1;
    _global_opt[0] = BIT_OPT_0_VOICE_OUTPUT;
    expect(section(state, PARAM_ANTIFONA1, "cross-ant").find(HTML_DIV_RUBRIC) != std::string::npos,
           "TTS no longer hides the repeated psalm opening");
    expect(section(state, PARAM_ZALM1, "cross-psalm").find(HTML_P_VERSE_CONT) != std::string::npos,
           "TTS no longer resumes after the psalm cross");

    _global_opt[0] = 0;
    _global_modlitba = MODL_CEZ_DEN_12;
    expect(section(state, PARAM_MODLITBA, "collect").find("Skrze Krista, nášho Pána.") != std::string::npos,
           "Daytime prayer lost its short conclusion");
    expect(section(state, PARAM_MODLITBA, "collect-lowercase").find("skrze Krista, nášho Pána.") != std::string::npos,
           "Lowercase prayer conclusion changed");
    expect(section(state, PARAM_MODLITBA, "collect-unknown").find("Skrze") == std::string::npos,
           "Unknown prayer conclusion reused previous text");
    _global_modlitba = MODL_VESPERY;
    expect(section(state, PARAM_MODLITBA, "collect").find("Skrze nášho Pána Ježiša Krista") != std::string::npos,
           "Vespers lost its long conclusion");
}

static std::string referenceTemplate() {
    initExport();
    char path[] = "tests/fixtures/prayer-reference-template.htm";
    interpretTemplate(PRM_DATUM, MODL_VESPERY, path, NIE);
    const std::string result = getExportedString();
    closeExport();
    return result;
}

static void checkTemplateReferences() {
    _global_modlitba = MODL_VESPERY;
    _global_opt[0] = BIT_OPT_0_REFERENCIE | BIT_OPT_0_FOOTNOTES;
    _global_opt[1] = BIT_OPT_1_CHVALOSPEVY;
    auto output = referenceTemplate();
    expect(output.find("dkc.php?in=Lk 1, 46-55") != std::string::npos,
           "Magnificat reference was not rendered as a Bible link");
    expect(output.find("Note before <a") != std::string::npos && output.find("</a> and after.") != std::string::npos,
           "Template footnote lost its nested reference");
    _global_opt[0] |= BIT_OPT_0_REF_BIBLE_COM;
    output = referenceTemplate();
    expect(output.find("https://www.bible.com/bible/163/LUK.1.46-55") != std::string::npos,
           "Template reference ignored the selected Bible provider");
    _global_opt[0] = 0;
    output = referenceTemplate();
    expect(output.find("Magnificat: 1, 46-55") != std::string::npos && output.find("<a") == std::string::npos,
           "Disabling references changed the visible citation or kept its hyperlink");
    _global_opt[0] = BIT_OPT_0_REFERENCIE;
    _global_opt[1] = 0;
    output = referenceTemplate();
    expect(output.find("1, 46-55") == std::string::npos && output.find("Outside the canticle.") != std::string::npos,
           "A reference exposed the disabled Magnificat");
    _global_opt[0] |= BIT_OPT_0_VOICE_OUTPUT;
    output = referenceTemplate();
    expect(output.find("1, 46-55") != std::string::npos && output.find("Note before") == std::string::npos,
           "Template references changed TTS canticle or footnote visibility");
}

int main(int argc, char** argv) {
    record = argc == 2 && std::string(argv[1]) == "--record";
    setenv("REQUEST_METHOD", "GET", 1);
    setenv("QUERY_STRING", "qt=pxml&j=sk", 1);
    const char* args[] = {"breviar.cgi", nullptr};
    breviar_main(1, args); // Initialize the same globals/options as CGI and JNI.
    _global_modlitba = MODL_VESPERY;
    _global_den.litobd = OBD_CEZ_ROK;
    const unsigned long long details = BIT_OPT_0_REFERENCIE | BIT_OPT_0_FOOTNOTES
        | BIT_OPT_0_VERSE | BIT_OPT_0_ITALICS_CONDITIONAL | BIT_OPT_0_ZALMY_FULL_TEXT;
    const unsigned long long modes[] = {0, details, details | BIT_OPT_0_REF_BIBLE_COM,
        details | BIT_OPT_0_VOICE_OUTPUT};
    const char* names[] = {"plain", "details", "bible-com", "tts"};
    for (unsigned i = 0; i < 4; ++i) {
        _global_opt[0] = modes[i];
        _global_opt[1] = i ? BIT_OPT_1_CHVALOSPEVY | BIT_OPT_1_SLAVA_OTCU
            | BIT_OPT_1_PLNE_RESP | BIT_OPT_1_PROSBY_ZVOLANIE : 0;
        _global_opt[2] = 0;

        initExport();
        includeFile(PRM_DATUM, MODL_VESPERY, PARAM_ZALM1,
            "tests/fixtures/prayer-sections.htm", "SaMpLe");
        check(std::string("section-") + names[i]);
        initExport();
        char path[] = "tests/fixtures/prayer-template.htm";
        interpretTemplate(PRM_DATUM, MODL_VESPERY, path, NIE);
        check(std::string("template-") + names[i]);
    }
    for (const char* anchor : {"alias-a", "alias-b", "repeat", "missing"}) {
        initExport();
        includeFile(PRM_DATUM, MODL_VESPERY, PARAM_ZALM1,
            "tests/fixtures/prayer-sections.htm", anchor);
        check(anchor);
    }
    checkInlineState();
    checkLiturgicalMarkers();
    checkTemplateReferences();
    if (failures) return 1;
    std::cout << "Prayer rendering fixtures passed\n";
}
