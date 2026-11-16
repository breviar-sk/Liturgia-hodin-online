#include "prayer-sharing.h"

#ifdef BREVIAR_WEB_SHARING
#include "breviar.h"
#include "html-markup.h"
#include "liturgia.h"
#include "myexpt.h"
#include "third_party/qrcodegen/qrcodegen.hpp"
#include <cstdlib>
#include <map>
#include <sstream>
#include <stdexcept>

namespace sharing {

std::string selection;
bool requested = false;

namespace {
const char* const publicUrl = "https://breviar.sk/cgi-bin/l.cgi?";
const char* const linkVersion = "1";

struct Text {
    const char* title;
    const char* message;
    const char* copy;
    const char* copied;
    const char* error;
    const char* close;
};
const Text translations[] = {
    {"Zdieľať modlitbu", "Naskenujte tento QR kód a otvorte stránku.", "Kopírovať odkaz", "Odkaz bol skopírovaný", "Túto stránku nemožno zdieľať.", "Zavrieť"},
    {"Sdílet modlitbu", "Naskenujte tento QR kód a otevřete stránku.", "Kopírovat odkaz", "Odkaz byl zkopírován", "Tuto stránku nelze sdílet.", "Zavřít"},
    {"Share prayer", "Scan this QR code to open the page.", "Copy link", "Link copied", "This page cannot be shared.", "Close"},
    {"Orationem communicare", "Hunc codicem QR lege ut paginam aperias.", "Vinculum exscribere", "Vinculum exscriptum", "Haec pagina communicari non potest.", "Claudere"},
    {}, // undefined language
    {"Sdílet modlitbu", "Naskenujte tento QR kód a otevřete stránku.", "Kopírovat odkaz", "Odkaz byl zkopírován", "Tuto stránku nelze sdílet.", "Zavřít"},
    {"Ima megosztása", "Olvassa be ezt a QR-kódot az oldal megnyitásához.", "Hivatkozás másolása", "Hivatkozás másolva", "Ez az oldal nem osztható meg.", "Bezárás"},
    {}, // ru: use English until translated
    {}, // by: use English until translated
    {"Deila bæn", "Skannaðu þennan QR-kóða til að opna síðuna.", "Afrita tengil", "Tengill afritaður", "Ekki er hægt að deila þessari síðu.", "Loka"},
    {"Compartir oración", "Escanea este código QR para abrir la página.", "Copiar enlace", "Enlace copiado", "Esta página no se puede compartir.", "Cerrar"},
    {"Duanı paylaş", "Səhifəni açmaq üçün bu QR kodunu skan edin.", "Keçidi kopyala", "Keçid kopyalandı", "Bu səhifəni paylaşmaq mümkün deyil.", "Bağla"},
};

static_assert(sizeof(translations) / sizeof(translations[0]) == POCET_JAZYKOV + 1,
    "Add sharing text when adding a language");

const Text& text() {
    return _global_jazyk >= 0 && _global_jazyk <= POCET_JAZYKOV && translations[_global_jazyk].title
        ? translations[_global_jazyk] : translations[JAZYK_EN];
}

std::string encode(const std::string& value) {
    std::string result;
    const char* hex = "0123456789ABCDEF";
    for (unsigned char c : value) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
            || c == '-' || c == '_' || c == '.' || c == '~') result += c;
        else { result += '%'; result += hex[c >> 4]; result += hex[c & 15]; }
    }
    return result;
}

void parameters(std::map<std::string, std::string>& result, std::string input) {
    for (std::size_t at = 0; (at = input.find("&amp;", at)) != std::string::npos; ++at)
        input.replace(at, 5, "&");
    std::istringstream stream(input);
    std::string pair;
    while (std::getline(stream, pair, '&')) {
        const auto equals = pair.find('=');
        if (equals != std::string::npos && equals > 0)
            result[pair.substr(0, equals)] = pair.substr(equals + 1);
    }
}

std::string currentQuery() {
    char options[MAX_STR] = {}, scratch[MAX_STR] = {};
    prilep_request_options(options, scratch);
    std::string resolved = options;
    // Include defaults too: recipients must receive the sender's effective
    // option words, regardless of platform defaults or their previous settings.
    for (int i = 0; i < POCET_GLOBAL_OPT; ++i)
        resolved += "&o" + std::to_string(i) + "=" + std::to_string(_global_opt[i]);
    return query(selection, resolved, skratka_jazyka[_global_jazyk],
        PODMIENKA_EXPORTOVAT_KALENDAR ? skratka_kalendara[_global_kalendar] : "");
}

std::string localUrl(const std::string& query) {
    std::string path = script_name;
    if (!path.empty() && path.front() != '/' && path.find("://") == std::string::npos) path.insert(0, "/");
    return path + "?" + query;
}
} // namespace

std::string query(const std::string& selection, const std::string& options,
                  const std::string& language, const std::string& calendar) {
    std::map<std::string, std::string> values;
    parameters(values, selection);
    parameters(values, options);
    values["j"] = language;
    values["k"] = calendar;
    values["sh"] = linkVersion;
    values.erase("share");
    values.erase("dl");
    std::string result;
    const auto append = [&](const std::string& key, const std::string& value) {
        if (!result.empty()) result += '&';
        result += encode(key) + "=" + encode(value);
    };
    for (const char* key : {"qt", "d", "m", "r", "p", "j", "k"}) {
        const auto found = values.find(key);
        if (found != values.end()) { append(found->first, found->second); values.erase(found); }
    }
    for (const auto& item : values) append(item.first, item.second);
    // Reserve the CGI sharing flag as well as the terminator.
    if (result.size() + std::string("&share=1").size() >= MAX_QUERY_STR)
        throw std::length_error("Prayer link exceeds the CGI query limit");
    return result;
}

std::string svg(const std::string& url) {
    const auto qr = qrcodegen::QrCode::encodeText(url.c_str(), qrcodegen::QrCode::Ecc::MEDIUM);
    const int border = 4, size = qr.getSize() + 2 * border;
    std::ostringstream output;
    output << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 " << size << ' ' << size
           << "\" role=\"img\" aria-label=\"QR\" shape-rendering=\"crispEdges\">"
           << "<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/><path fill=\"#000000\" d=\"";
    for (int y = 0; y < qr.getSize(); ++y)
        for (int x = 0; x < qr.getSize(); ++x)
            if (qr.getModule(x, y)) output << 'M' << x + border << ',' << y + border << "h1v1h-1z ";
    output << "\"/></svg>";
    return output.str();
}

std::string withFragment(const std::string& url, const std::string& encodedFragment) {
    if (encodedFragment.empty()) return url;
    const auto hex = [](char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    };
    std::string decoded;
    for (std::size_t i = 0; i < encodedFragment.size(); ++i) {
        if (encodedFragment[i] == '%' && i + 2 < encodedFragment.size()) {
            const int high = hex(encodedFragment[i + 1]), low = hex(encodedFragment[i + 2]);
            if (high >= 0 && low >= 0) {
                decoded += static_cast<char>((high << 4) | low);
                i += 2;
                continue;
            }
        }
        // Unlike form data, a literal '+' in a fragment is never a space.
        decoded += encodedFragment[i];
    }
    return url + '#' + encode(decoded);
}

void menu(FILE* output) {
    if (selection.empty()) return;
    std::string target = "#prayer-share-panel";
    try { target = localUrl(currentQuery()) + "&share=1"; }
    catch (const std::length_error&) {} // The panel will explain an oversized link.
    Export_to_file(output, "<a class=\"prayer-share-action\" href=\"%s\">%s</a>\n",
        prayer::escapeHtmlAttribute(target).c_str(), text().title);
}

void panel() {
    if (selection.empty()) return;
    std::string url, target, close = "#", image;
    bool failed = false;
    try {
        const auto params = currentQuery();
        url = publicUrl + params;
        // Fragments never reach CGI in a URL. Keep this transport outside the
        // prayer query and its legacy parameter-size limits.
        if (requested) {
            if (const auto* fragment = std::getenv("HTTP_X_BREVIAR_SHARE_FRAGMENT"))
                url = withFragment(url, fragment);
        }
        close = localUrl(params);
        target = close + "&share=1";
        if (requested) image = svg(url);
    } catch (const std::length_error&) { failed = true; }
    const auto& t = text();
    Export("<section id=\"prayer-share-panel\" class=\"prayer-share-panel\"%s role=\"dialog\" aria-modal=\"true\""
           " aria-labelledby=\"prayer-share-title\" data-action=\"%s\" data-url=\"%s\" data-copied=\"%s\" data-error=\"%s\">\n",
        requested ? "" : " hidden", prayer::escapeHtmlAttribute(target).c_str(),
        prayer::escapeHtmlAttribute(url).c_str(), prayer::escapeHtmlAttribute(t.copied).c_str(),
        prayer::escapeHtmlAttribute(t.error).c_str());
    Export("<div class=\"prayer-share-window\"><header class=\"prayer-share-toolbar\">"
           "<a class=\"prayer-share-close\" href=\"%s\" aria-label=\"%s\">&#215;</a>"
           "<span id=\"prayer-share-title\">%s</span></header><div class=\"prayer-share-body\">"
           "<p>%s</p>%s<button type=\"button\" class=\"prayer-share-copy\"%s>%s</button>"
           "<p class=\"prayer-share-status\" role=\"status\"></p></div></div></section>\n"
           "<script src=\"/prayer-sharing.js\"></script>\n",
        prayer::escapeHtmlAttribute(close).c_str(), t.close, t.title, failed ? t.error : t.message,
        image.c_str(), failed ? " hidden" : "", t.copy);
}
} // namespace sharing
#endif
