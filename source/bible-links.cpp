#include "bible-links.h"
#include "utf8-utils.h"
#include <utility>

namespace bible {
namespace {

// Filenames and chapter anchors checked against both Vatican indexes, 2026-11-09.
// https://www.vatican.va/archive/bible/nova_vulgata/documents/nova-vulgata_index_lt.html
struct VaticanBook { const char* file; unsigned chapters; };
const VaticanBook vaticanBooks[] = {
    {"nova-vulgata_vt_genesis_lt.html", 50}, // Gen
    {"nova-vulgata_vt_exodus_lt.html", 40}, // Exod
    {"nova-vulgata_vt_leviticus_lt.html", 27}, // Lev
    {"nova-vulgata_vt_numeri_lt.html", 36}, // Num
    {"nova-vulgata_vt_deuteronomii_lt.html", 34}, // Deut
    {"nova-vulgata_vt_iosue_lt.html", 24}, // Josh
    {"nova-vulgata_vt_iudicum_lt.html", 21}, // Judg
    {"nova-vulgata_vt_ruth_lt.html", 4}, // Ruth
    {"nova-vulgata_vt_i-samuelis_lt.html", 31}, // Sam1
    {"nova-vulgata_vt_ii-samuelis_lt.html", 24}, // Sam2
    {"nova-vulgata_vt_i-regum_lt.html", 22}, // Kgs1
    {"nova-vulgata_vt_ii-regum_lt.html", 25}, // Kgs2
    {"nova-vulgata_vt_i-paralipomenon_lt.html", 29}, // Chr1
    {"nova-vulgata_vt_ii-paralipomenon_lt.html", 36}, // Chr2
    {"nova-vulgata_vt_esdrae_lt.html", 10}, // Ezra
    {"nova-vulgata_vt_nehemiae_lt.html", 13}, // Neh
    {"nova-vulgata_vt_esther_lt.html", 10}, // Esth
    {"nova-vulgata_vt_iob_lt.html", 42}, // Job
    {"nova-vulgata_vt_psalmorum_lt.html", 150}, // Ps
    {"nova-vulgata_vt_proverbiorum_lt.html", 31}, // Prov
    {"nova-vulgata_vt_ecclesiastes_lt.html", 12}, // Eccl
    {"nova-vulgata_vt_canticum-canticorum_lt.html", 8}, // Song
    {"nova-vulgata_vt_isaiae_lt.html", 66}, // Isa
    {"nova-vulgata_vt_ieremiae_lt.html", 52}, // Jer
    {"nova-vulgata_vt_lamentationes_lt.html", 5}, // Lam
    {"nova-vulgata_vt_ezechielis_lt.html", 48}, // Ezek
    {"nova-vulgata_vt_danielis_lt.html", 14}, // Dan
    {"nova-vulgata_vt_osee_lt.html", 14}, // Hos
    {"nova-vulgata_vt_ioel_lt.html", 4}, // Joel
    {"nova-vulgata_vt_amos_lt.html", 9}, // Amos
    {"nova-vulgata_vt_abdiae_lt.html", 1}, // Obad
    {"nova-vulgata_vt_ionae_lt.html", 4}, // Jonah
    {"nova-vulgata_vt_michaeae_lt.html", 7}, // Mic
    {"nova-vulgata_vt_nahum_lt.html", 3}, // Nah
    {"nova-vulgata_vt_habacuc_lt.html", 3}, // Hab
    {"nova-vulgata_vt_sophoniae_lt.html", 3}, // Zeph
    {"nova-vulgata_vt_aggaei_lt.html", 2}, // Hag
    {"nova-vulgata_vt_zachariae_lt.html", 14}, // Zech
    {"nova-vulgata_vt_malachiae_lt.html", 3}, // Mal
    {"nova-vulgata_nt_evang-matthaeum_lt.html", 28}, // Matt
    {"nova-vulgata_nt_evang-marcum_lt.html", 16}, // Mark
    {"nova-vulgata_nt_evang-lucam_lt.html", 24}, // Luke
    {"nova-vulgata_nt_evang-ioannem_lt.html", 21}, // John
    {"nova-vulgata_nt_actus-apostolorum_lt.html", 28}, // Acts
    {"nova-vulgata_nt_epist-romanos_lt.html", 16}, // Rom
    {"nova-vulgata_nt_epist-i-corinthios_lt.html", 16}, // Cor1
    {"nova-vulgata_nt_epist-ii-corinthios_lt.html", 13}, // Cor2
    {"nova-vulgata_nt_epist-galatas_lt.html", 6}, // Gal
    {"nova-vulgata_nt_epist-ephesios_lt.html", 6}, // Eph
    {"nova-vulgata_nt_epist-philippenses_lt.html", 4}, // Phil
    {"nova-vulgata_nt_epist-colossenses_lt.html", 4}, // Col
    {"nova-vulgata_nt_epist-i-thessalonicenses_lt.html", 5}, // Thess1
    {"nova-vulgata_nt_epist-ii-thessalonicenses_lt.html", 3}, // Thess2
    {"nova-vulgata_nt_epist-i-timotheum_lt.html", 6}, // Tim1
    {"nova-vulgata_nt_epist-ii-timotheum_lt.html", 4}, // Tim2
    {"nova-vulgata_nt_epist-titum_lt.html", 3}, // Titus
    {"nova-vulgata_nt_epist-philemonem_lt.html", 1}, // Phlm
    {"nova-vulgata_nt_epist-hebraeos_lt.html", 13}, // Heb
    {"nova-vulgata_nt_epist-iacobi_lt.html", 5}, // Jas
    {"nova-vulgata_nt_epist-i-petri_lt.html", 5}, // Pet1
    {"nova-vulgata_nt_epist-ii-petri_lt.html", 3}, // Pet2
    {"nova-vulgata_nt_epist-i-ioannis_lt.html", 5}, // John1
    {"nova-vulgata_nt_epist-ii-ioannis_lt.html", 1}, // John2
    {"nova-vulgata_nt_epist-iii-ioannis_lt.html", 1}, // John3
    {"nova-vulgata_nt_epist-iudae_lt.html", 1}, // Jude
    {"nova-vulgata_nt_apocalypsis-ioannis_lt.html", 22}, // Rev
    {"nova-vulgata_vt_thobis_lt.html", 14}, // Tob
    {"nova-vulgata_vt_iudith_lt.html", 16}, // Jdt
    {"nova-vulgata_vt_sapientiae_lt.html", 19}, // Wis
    {"nova-vulgata_vt_ecclesiasticus_lt.html", 51}, // Sir
    {"nova-vulgata_vt_baruch_lt.html", 6}, // Bar
    {"nova-vulgata_vt_i-maccabaeorum_lt.html", 16}, // Macc1
    {"nova-vulgata_vt_ii-maccabaeorum_lt.html", 15}, // Macc2
};
static_assert(sizeof(vaticanBooks) / sizeof(vaticanBooks[0]) == static_cast<unsigned>(BookId::Count),
              "Every Bible book needs a Vatican document");

std::string encodeComponent(const std::string& value) {
    const char hex[] = "0123456789ABCDEF";
    std::string result;
    for (unsigned char c : value) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' || c == '~') {
            result += static_cast<char>(c);
        } else {
            result += '%';
            result += hex[c >> 4];
            result += hex[c & 15];
        }
    }
    return result;
}

std::string referenceText(const std::string& text, bool removeDiacritics) {
    std::string result;
    Utf8DecoderState state;
    InitUtf8DecoderState(&state);
    for (char byte : text) {
        if (!Utf8StreamingDecoder(byte, &state)) continue;
        int c = state.result;
        if (removeDiacritics) c = RemoveDiacriticsFromWchar(c);
        if (c == '_' || c == 0x7f || c == 0xa0 || c == 0x2009 || c == 0x202f) c = ' ';
        if (c == 0x2014) c = 0x2013; // Keep the existing text-provider convention.
        char encoded[5] = {};
        char* end = encoded;
        EncodeWchar(c, &end);
        result.append(encoded, end);
    }
    return result;
}

unsigned modernPsalm(const Location& location, PsalmNumbering numbering) {
    const unsigned n = location.chapter;
    if (n == 0 || n > 150) return 0;
    if (numbering == PsalmNumbering::Modern) return n;
    unsigned first = n, last = n;
    if (n == 9) { first = 9; last = 10; }
    else if (n >= 10 && n <= 112) first = last = n + 1;
    else if (n == 113) { first = 114; last = 115; }
    else if (n == 114 || n == 115) first = last = 116;
    else if (n >= 116 && n <= 145) first = last = n + 1;
    else if (n == 146 || n == 147) first = last = 147;
    if (first != last && location.psalmPart == 'a') last = first;
    if (first != last && location.psalmPart == 'b') first = last;
    if (location.alternatePsalm) {
        return location.alternatePsalm >= first && location.alternatePsalm <= last
            ? location.alternatePsalm : 0;
    }
    if (first == last) return first;
    // Traditional Psalms 9 and 113 each span two modern Psalms. Without an
    // explicit alternate number/part, linking the book avoids guessing.
    return 0;
}

} // namespace

LinkResult::LinkResult(std::string url, LinkDetail detail)
    : url(std::move(url)), detail(detail) {}

TextReferenceProvider::TextReferenceProvider(std::string prefix, bool removeDiacritics)
    : prefix_(std::move(prefix)), removeDiacritics_(removeDiacritics) {}

LinkResult TextReferenceProvider::link(const Reference& reference) const {
    if (prefix_.empty() || reference.text.empty()) return {};
    return {prefix_ + encodeComponent(referenceText(reference.text, removeDiacritics_)), LinkDetail::Text};
}

BibleComProvider::BibleComProvider(std::string baseUrl, std::string edition)
    : baseUrl_(std::move(baseUrl)), edition_(std::move(edition)) {}

LinkResult BibleComProvider::link(const Reference& reference) const {
    if (baseUrl_.empty() || edition_.empty() || reference.book == BookId::Unknown) return {};
    // Configuration placeholders are not real edition IDs.
    if (edition_.find_first_not_of("0123456789") != std::string::npos) return {};
    std::string url = baseUrl_ + (baseUrl_.back() == '/' ? "" : "/") + edition_ + "/" + bookCode(reference.book);
    if (reference.passages.empty()) return {url, LinkDetail::Book};
    const auto& first = reference.passages.front().first;
    url += "." + std::to_string(first.chapter);
    if (!first.verse) return {url, LinkDetail::Chapter};
    url += ".";
    // Bible.com supports verse ranges/lists in one chapter. More complicated
    // references still link to the first passage, never to a fabricated URL.
    bool comma = false;
    for (const auto& passage : reference.passages) {
        if (passage.book != reference.book || passage.first.chapter != first.chapter || !passage.first.verse)
            break;
        if (comma) url += ',';
        url += std::to_string(passage.first.verse);
        if (passage.last.chapter != first.chapter) break;
        if (passage.last.verse != passage.first.verse) url += "-" + std::to_string(passage.last.verse);
        comma = true;
    }
    return {url, LinkDetail::Verse};
}

const char* NovaVulgataProvider::baseUrl() {
    return "https://www.vatican.va/archive/bible/nova_vulgata/documents/";
}

NovaVulgataProvider::NovaVulgataProvider(PsalmNumbering numbering) : numbering_(numbering) {}

LinkResult NovaVulgataProvider::link(const Reference& reference) const {
    const auto index = static_cast<unsigned>(reference.book);
    if (index >= static_cast<unsigned>(BookId::Count)) return {};
    const auto& book = vaticanBooks[index];
    const std::string url = std::string(baseUrl()) + book.file;
    // Single-chapter documents have no numeric chapter anchors.
    if (reference.passages.empty() || book.chapters == 1) return {url, LinkDetail::Book};
    const auto& location = reference.passages.front().first;
    if (reference.book == BookId::Ps) {
        const unsigned psalm = modernPsalm(location, numbering_);
        if (!psalm) return {url, LinkDetail::Book};
        return {url + "#PSALMUS%20" + std::to_string(psalm), LinkDetail::Chapter};
    }
    if (location.chapter == 0 || location.chapter > book.chapters) return {url, LinkDetail::Book};
    return {url + "#" + std::to_string(location.chapter), LinkDetail::Chapter};
}

BibleLinks::BibleLinks(Language language, const LinkSettings& settings) : language_(language) {
    if (settings.useBibleCom)
        provider_.reset(new BibleComProvider(settings.bibleComBase, settings.bibleComEdition));
    else if (settings.referenceBase == NovaVulgataProvider::baseUrl())
        provider_.reset(new NovaVulgataProvider(language == Language::Latin || language == Language::Spanish
            ? PsalmNumbering::Traditional : PsalmNumbering::Modern));
    else
        provider_.reset(new TextReferenceProvider(settings.referenceBase, settings.removeDiacritics));
}

LinkResult BibleLinks::link(const std::string& prefix, const std::string& label) const {
    const auto target = prefix.empty() ? label : prefix + " " + label;
    return provider_->link(parseReference(target, language_));
}

} // namespace bible
