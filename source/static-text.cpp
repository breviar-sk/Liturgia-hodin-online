#include "static-text.h"
#include "prayer-renderer.h"
#include "breviar.h"
#include "mydefs.h"
#include "liturgia.h"

namespace prayer {

short ordinariumPrayer(short prayer) {
    return prayer >= MODL_INVITATORIUM && prayer <= MODL_KOMPLETORIUM
        ? prayer : MODL_RANNE_CHVALY;
}

StaticPage staticPage(const std::string& name) {
    struct Page { const char* name; const char* file; const char* anchor; };
    static const Page pages[] = {
        {"psalm-95", "z95.htm", "ZALM95"},
        {"psalm-100", "z100.htm", "ZALM100"},
        {"psalm-67", "z67.htm", "ZALM67"},
        {"psalm-24", "z24.htm", "ZALM24"},
        {"lord-prayer", "doduvodmp.htm", "_OTCENAS-UVOD"},
        {"intercessions", "dodprosby.htm", "SUPPLEMENT"},
        {"penitential-act", "cezrok_k.htm", "_k_UKONKAJ"},
        {"extended-vigil", "ord_vigil.htm", "ORDINARIUM"},
        {"guidelines", "static-unavailable.htm", "INFO"},
    };
    for (const auto& page : pages) {
        if (name == page.name) {
            StaticPage result;
            result.file = page.file;
            result.anchor = page.anchor;
            return result;
        }
    }
    return {};
}

namespace {

std::string queryLink(const std::string& selection) {
    // Reuse the option builder used by the prayer templates. It returns HTML
    // separators; keep URLs unescaped until the inline renderer writes HTML.
    char options[MAX_STR] = {}, scratch[MAX_STR] = {};
    prilep_request_options(options, scratch);
    std::string suffix = options;
    for (std::size_t at = 0; (at = suffix.find("&amp;", at)) != std::string::npos; ++at)
        suffix.replace(at, 5, "&");
    if (suffix.find("&j=") == std::string::npos)
        suffix += std::string("&j=") + skratka_jazyka[_global_jazyk];
    std::string script = script_name;
    // A CGI path must not resolve relative to the current CGI directory.
    if (!script.empty() && script.front() != '/' && script.find("://") == std::string::npos)
        script.insert(0, "/");
    return script + "?qt=pst&" + selection + suffix;
}

} // namespace

std::string contentLink(const std::string& target) {
    const auto hash = target.find('#');
    const auto name = target.substr(0, hash);
    const auto fragment = hash == std::string::npos ? std::string() : target.substr(hash);
    std::string url;
    if (name == "marian-antiphons") url = queryLink("st=1");
    else if (name.compare(0, 11, "ordinarium-") == 0) {
        const auto office = name.substr(11);
        // Use canonical office identifiers rather than unvalidated URL text.
        for (short p = MODL_INVITATORIUM; p <= MODL_KOMPLETORIUM; ++p) {
            if (office == str_modlitby[p]) {
                url = queryLink("st=2&p=" + office);
                break;
            }
        }
    } else if (name == "guidelines" && (_global_jazyk == JAZYK_SK || _global_jazyk == JAZYK_LA)) {
        // Only Slovak and Latin editions contain this standalone document.
        url = _global_jazyk == JAZYK_LA ? "https://breviar.sk/la/docs/smernice_lh.htm"
                                       : "https://breviar.sk/docs/smernice_lh.htm";
    } else if (*staticPage(name).file) url = queryLink("st=text&p=" + name);
    return url.empty() ? url : url + fragment;
}

void renderStaticPage(RenderState& state, short type, short prayer, const char* part,
                      const char* path, const char* anchor) {
    const auto result = renderSection(state, type, prayer, part, path, anchor, false);
    if (result == SectionResult::Rendered || result == SectionResult::Skipped) return;
    const std::string filename = path;
    const auto slash = filename.find_last_of("/\\");
    const std::string fallback = (slash == std::string::npos ? std::string() : filename.substr(0, slash + 1))
        + "static-unavailable.htm";
    renderSection(state, type, prayer, part, fallback.c_str(), "INFO");
}

} // namespace prayer
