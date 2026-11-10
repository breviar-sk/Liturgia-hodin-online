#include "bible-reference.h"
#include "utf8-utils.h"
#include <cstddef>
#include <map>
#include <utility>

namespace bible {
namespace {

constexpr unsigned languageCount = static_cast<unsigned>(Language::Unknown);

struct Book {
    const char* code;
    unsigned chapters;
    // Slovak, Czech, Latin, Hungarian, Icelandic, Spanish, Azerbaijani, English.
    // Alternative spellings are separated by |; whitespace and case are ignored.
    const char* aliases[languageCount];
    // Conflicting aliases (e.g. Icelandic Sk and untranslated Slovak Sk) are
    // deliberately unresolved, rather than silently choosing the wrong book.
};

const Book books[] = {
    {"GEN", 50, {"Gn", "Gn", "Gen|Gn", "Ter", "1M|Gn", "Gn", "Yar", "Gen"}}, // Gen
    {"EXO", 40, {"Ex", "Ex", "Ex", "Ex|Kiv", "2M|Ex", "Ex", "Çıx", "Exod"}}, // Exod
    {"LEV", 27, {"Lv", "Lv", "Lev|Lv", "Lev", "3M|Lv", "Lv", "Lv", "Lev"}}, // Lev
    {"NUM", 36, {"Nm", "Nm|Num", "Num|Nm", "Szám", "4M|Nm", "Nm", "Say", "Num"}}, // Num
    {"DEU", 34, {"Dt", "Dt", "Deut|Dt", "MTörv", "5M|Dt", "Dt", "Qanun|QanTək", "Deut"}}, // Deut
    {"JOS", 24, {"Joz", "Joz", "Ios|Joz", "Joz|Józs", "Js|Joz", "Jos", "Yeşua", "Josh"}}, // Josh
    {"JDG", 21, {"Sdc", "Sd", "Iudic|Sdc", "Bír", "Dm|Sdc", "Jue", "Hak", "Judg"}}, // Judg
    {"RUT", 4, {"Rút", "Rt", "Rut|Rút", "Rut", "Rt|Rút", "Rt", "Rut", "Ruth"}}, // Ruth
    {"1SA", 31, {"1Sam", "1Sam", "1Sam", "1Sám", "1S|1Sam|1Sm", "1Sm", "1Şam", "1Sam"}}, // Sam1
    {"2SA", 24, {"2Sam", "2Sam", "2Sam", "2Sám", "2S|2Sam|2Sm", "2Sm", "2Şam", "2Sam"}}, // Sam2
    {"1KI", 22, {"1Kr", "1Kr|1Král", "1Reg|1Kr", "1Kir", "1Kon|1Kr", "1Re", "1Pad", "1Kgs"}}, // Kgs1
    {"2KI", 25, {"2Kr", "2Kr|2Král", "2Reg|2Kr", "2Kir", "2Kon|2Kr", "2Re", "2Pad", "2Kgs"}}, // Kgs2
    {"1CH", 29, {"1Krn", "1Krn|1Kron", "1Chr|1Krn", "1Krón", "1Kro|1Krn", "1Cr", "1Saln", "1Chr"}}, // Chr1
    {"2CH", 36, {"2Krn", "2Krn|2Kron", "2Chr|2Krn", "2Krón", "2Kro|2Krn", "2Cr", "2Saln", "2Chr"}}, // Chr2
    {"EZR", 10, {"Ezd", "Ezd", "Esd|Ezd", "Ezd", "Esr|Ezd", "Esd", "Ezra", "Ezra"}}, // Ezra
    {"NEH", 13, {"Neh", "Neh", "Neh", "Neh", "Neh", "Neh", "Neh", "Neh"}}, // Neh
    {"EST", 16, {"Est", "Est", "Est", "Eszt", "Est", "Est", "Est", "Esth"}}, // Esth
    {"JOB", 42, {"Jób", "Jób|Job", "Iob|Jób", "Jób", "Jb|Jób", "Job", "Əyyub", "Job"}}, // Job
    {"PSA", 150, {"Ž|Ps", "Žl", "Ps|Ž", "Zsolt", "S|Ž|Sl", "Sal", "Z|Məzmur|Ps", "Ps"}}, // Ps
    {"PRO", 31, {"Prís", "Př|Přís", "Prov|Prís", "Péld", "Ok|Prís", "Pr", "SülMəs", "Prov"}}, // Prov
    {"ECC", 12, {"Kaz", "Kaz", "Qoh|Kaz", "Préd", "Pd|Kaz", "Qo", "Vaiz", "Eccl"}}, // Eccl
    {"SNG", 8, {"Pies", "Pís", "Cant|Pies", "Én", "Ll|Pies", "Ct", "Nəğ", "Song"}}, // Song
    {"ISA", 66, {"Iz", "Iz", "Is|Iz", "Iz", "Jes|Iz", "Is", "Yeş", "Isa"}}, // Isa
    {"JER", 52, {"Jer", "Jer", "Ier|Jer", "Jer", "Jer", "Jr", "Yer", "Jer"}}, // Jer
    {"LAM", 5, {"Nár", "Nář|Pláč", "Lam|Nár", "Siral|Siralm", "Hl|Nár", "Lm", "Mərs", "Lam"}}, // Lam
    {"EZK", 48, {"Ez", "Ez", "Ez", "Ez", "Esk|Ez", "Ez", "Yez", "Ezek"}}, // Ezek
    {"DAN", 14, {"Dan", "Dan", "Dan", "Dán", "Dn|Dan", "Dn|Dan", "Dan", "Dan"}}, // Dan
    {"HOS", 14, {"Oz", "Oz", "Os|Oz", "Oz|Óz", "Hs|Oz", "Os", "Huşə", "Hos"}}, // Hos
    {"JOL", 4, {"Joel", "Jl", "Ioel|Joel", "Joel", "Jl|Joel", "Jl", "Yoel", "Joel"}}, // Joel
    {"AMO", 9, {"Am", "Am", "Am", "Am|Ám", "Am", "Am", "Amos", "Amos"}}, // Amos
    {"OBA", 1, {"Abd", "Abd", "Abd", "Abd", "Ob|Abd", "Ab", "Avd", "Obad"}}, // Obad
    {"JON", 4, {"Jon", "Jon", "Ion|Jon", "Jon", "Jnh|Jon", "Jon", "Yun", "Jonah"}}, // Jonah
    {"MIC", 7, {"Mich", "Mich", "Mic|Mich", "Mik", "Mík|Mich", "Mi", "Mich", "Mic"}}, // Mic
    {"NAM", 3, {"Nah", "Nah", "Nah", "Nah|Náh", "Na|Nah", "Na", "Nah", "Nah"}}, // Nah
    {"HAB", 3, {"Hab", "Hab", "Hab", "Hab", "Hb|Hab", "Ha", "Hab", "Hab"}}, // Hab
    {"ZEP", 3, {"Sof", "Sof", "Soph|Sof", "Sof|Szof", "Sf|Sof", "So", "Sef", "Zeph"}}, // Zeph
    {"HAG", 2, {"Ag", "Ag", "Agg|Ag", "Ag|Agg", "Hg|Ag", "Ag", "Haq", "Hag"}}, // Hag
    {"ZEC", 14, {"Zach", "Zach", "Zac|Zach", "Zak", "Sk|Zach", "Za", "Zək", "Zech"}}, // Zech
    {"MAL", 4, {"Mal", "Mal", "Mal", "Mal", "Ml|Mal", "Ml", "Mal", "Mal"}}, // Mal
    {"MAT", 28, {"Mt", "Mt", "Mt", "Mt", "Mt", "Mt", "Mt", "Matt"}}, // Matt
    {"MRK", 16, {"Mk", "Mk", "Mc|Mk", "Mk", "Mk", "Mc", "Mk|Mark", "Mark"}}, // Mark
    {"LUK", 24, {"Lk|Lc", "Lk", "Lc|Lk", "Lk", "Lk", "Lc", "Lk|Luka", "Luke"}}, // Luke
    {"JHN", 21, {"Jn", "Jan", "Io|Jn|Jan", "Jn|Ján", "Jh|Jn", "Jn", "Yəh", "John"}}, // John
    {"ACT", 28, {"Sk", "Sk", "Act|Sk", "ApCsel", "P|Sk", "Hch", "Həv|Həvİş|Həvarilərinİşləri", "Acts"}}, // Acts
    {"ROM", 16, {"Rim", "Řím", "Rom|Rim", "Róm", "Rm|Rim", "Rm", "Rom|Romalılara", "Rom"}}, // Rom
    {"1CO", 16, {"1Kor|1Cor", "1Kor", "1Cor|1Kor", "1Kor", "1Kor", "1Co", "1Kor", "1Cor"}}, // Cor1
    {"2CO", 13, {"2Kor", "2Kor", "2Cor|2Kor", "2Kor", "2Kor|2Kór", "2Co", "2Kor", "2Cor"}}, // Cor2
    {"GAL", 6, {"Gal", "Gal", "Gal", "Gal", "Gl|Gal", "Ga", "Qal", "Gal"}}, // Gal
    {"EPH", 6, {"Ef", "Ef", "Eph|Ef", "Ef", "Ef", "Ef", "Ef", "Eph"}}, // Eph
    {"PHP", 4, {"Flp", "Flp|Fil", "Phil|Flp", "Fil", "Fil|Flp|Fl", "Flp", "Flp", "Phil"}}, // Phil
    {"COL", 4, {"Kol", "Kol", "Col|Kol", "Kol", "Kól|Kol|Kl", "Col", "Kol", "Col"}}, // Col
    {"1TH", 5, {"1Sol", "1Sol|1Tes", "1Th|1Sol", "1Tessz|1Tesz", "1Þ|1Sol", "1Ts", "1Sal", "1Thess"}}, // Thess1
    {"2TH", 3, {"2Sol", "2Sol", "2Th|2Sol", "2Tessz", "2Þ|2Sol", "2Ts", "2Sal", "2Thess"}}, // Thess2
    {"1TI", 6, {"1Tim", "1Tim", "1Tim", "1Tim", "1Tm|1Tim", "1Tm", "1Tim", "1Tim"}}, // Tim1
    {"2TI", 4, {"2Tim", "2Tim", "2Tim", "2Tim", "2Tm|2Tim", "2Tm", "2Tim", "2Tim"}}, // Tim2
    {"TIT", 3, {"Tít", "Tit", "Tit|Tít", "Tít|Tit", "Tt|Tít", "Tt", "Tit", "Titus"}}, // Titus
    {"PHM", 1, {"Flm", "Flm", "Phlm|Flm", "Flm", "Flm", "Flm", "Flm", "Phlm"}}, // Phlm
    {"HEB", 13, {"Hebr|Žid", "Žid", "Hebr", "Zsid", "Heb|Hebr", "Hb", "İbr|İbranilərə", "Heb"}}, // Heb
    {"JAS", 5, {"Jak", "Jak", "Iac|Jak|Jac", "Jak", "Jk|Jak", "St", "Yaq", "Jas"}}, // Jas
    {"1PE", 5, {"1Pt", "1Petr", "1Petr|1Pt", "1Pét", "1Pt", "1Pe", "1Pt", "1Pet"}}, // Pet1
    {"2PE", 3, {"2Pt", "2Petr", "2Petr|2Pt", "2Pét", "2Pt", "2Pe", "2Pt", "2Pet"}}, // Pet2
    {"1JN", 5, {"1Jn", "1Jan", "1Io|1Jn", "1Jn", "1Jh|1Jn", "1Jn", "1Yəh", "1John"}}, // John1
    {"2JN", 1, {"2Jn", "2Jan", "2Io|2Jn", "2Jn", "2Jh|2Jn", "2Jn", "2Yəh", "2John"}}, // John2
    {"3JN", 1, {"3Jn", "3Jan", "3Io|3Jn", "3Jn", "3Jh|3Jn", "3Jn", "3Yəh", "3John"}}, // John3
    {"JUD", 1, {"Júd", "Júd|Jud", "Iud|Júd", "Júd", "Jd|Júd", "Judas", "Yhd", "Jude"}}, // Jude
    {"REV", 22, {"Zjv|Ap", "Zj", "Ap|Zjv", "Jel", "Opb|Zjv|Op", "Ap", "Vəhy", "Rev"}}, // Rev
    {"TOB", 14, {"Tob", "Tob", "Tob", "Tób", "Tb|Tob", "Tb", "Tov", "Tob"}}, // Tob
    {"JDT", 16, {"Jdt", "Jdt", "Iudt|Jdt", "Jdt|Jud|Judit", "Jdt", "Jdt", "Ydt", "Jdt"}}, // Jdt
    {"WIS", 19, {"Múd|Múdr", "Mdr", "Sap|Múd", "Bölcs", "SS|Múd", "Sb", "Müd", "Wis"}}, // Wis
    {"SIR", 51, {"Sir", "Sir", "Sir", "Sir", "Sr|Sir", "Si", "Sir", "Sir"}}, // Sir
    {"BAR", 6, {"Bar", "Bar", "Bar", "Bar|Bár", "Br|Bar", "Ba", "Bar", "Bar"}}, // Bar
    {"1MA", 16, {"1Mach", "1Mak", "1Mac|1Mach", "1Mak", "1Mkk|1Mach", "1Mc", "1Mak", "1Macc"}}, // Macc1
    {"2MA", 15, {"2Mach|2Mak", "2Mak", "2Mac|2Mach", "2Mak|2Makk", "2Mkk|2Mach", "2Mc", "2Mak", "2Macc"}}, // Macc2
};
static_assert(sizeof(books) / sizeof(books[0]) == static_cast<unsigned>(BookId::Count),
              "Every Bible book needs metadata");

// Normalize only for parsing. Display labels and custom-provider text are kept.
std::string normalized(const std::string& text) {
    std::string source = text;
    for (size_t at = source.find("<!--"); at != std::string::npos; at = source.find("<!--")) {
        const size_t end = source.find("-->", at + 4);
        if (end == std::string::npos) break;
        source.erase(at, end + 3 - at);
    }
    std::string result;
    Utf8DecoderState state;
    InitUtf8DecoderState(&state);
    for (unsigned char byte : source) {
        if (!Utf8StreamingDecoder(static_cast<char>(byte), &state)) continue;
        int c = WcharToLowercase(state.result);
        if (c == ' ' || c == '_' || c == '\t' || c == '\r' || c == '\n' ||
            c == 0x7f || c == 0xa0 || c == 0x2009 || c == 0x202f) continue;
        if (c == 0x2013 || c == 0x2014 || c == 0x2212) c = '-';
        char encoded[5] = {};
        char* end = encoded;
        EncodeWchar(c, &end);
        result.append(encoded, end);
    }
    // References may contain HTML spaces, as well as the renderer's _ notation.
    for (const char* space : {"&nbsp;", "&thinsp;", "&#160;", "&#8239;"}) {
        const std::string token(space);
        for (size_t at = result.find(token); at != std::string::npos; at = result.find(token))
            result.erase(at, token.size());
    }
    return result;
}

using Aliases = std::map<std::string, BookId>;
const std::vector<Aliases>& aliases() {
    // Construct once; the catalogue is immutable, including across CGI requests.
    static const std::vector<Aliases> result = [] {
        std::vector<Aliases> languages(languageCount);
        for (unsigned i = 0; i < static_cast<unsigned>(BookId::Count); ++i) {
            for (unsigned language = 0; language < languages.size(); ++language) {
                const std::string names = books[i].aliases[language];
                size_t begin = 0;
                do {
                    const size_t end = names.find('|', begin);
                    const auto key = normalized(names.substr(begin, end - begin));
                    if (!key.empty()) {
                        const auto inserted = languages[language].emplace(key, static_cast<BookId>(i));
                        if (!inserted.second && inserted.first->second != static_cast<BookId>(i))
                            inserted.first->second = BookId::Unknown;
                    }
                    if (end == std::string::npos) break;
                    begin = end + 1;
                } while (true);
            }
        }
        return languages;
    }();
    return result;
}

bool digit(char c) { return c >= '0' && c <= '9'; }

class Parser {
public:
    Parser(const std::string& text, Language language)
        : text_(normalized(text)), language_(language) {}

    Reference parse(const std::string& original) {
        Reference result;
        result.text = original;
        // These introduce a comparison, not a different book.
        for (const char* prefix : {"cf.", "cfr.", "porov.", "srv.", "srov.", "sbr.", "bax"}) {
            const std::string value(prefix);
            if (text_.compare(0, value.size(), value) == 0) { at_ += value.size(); break; }
        }
        BookId book = readBook();
        result.book = book;
        if (book == BookId::Unknown) return result;
        if (end()) { result.complete = true; return result; }
        unsigned verseChapter = 0;
        Location previous;
        do {
            Passage passage;
            passage.book = book;
            if (!location(book, verseChapter, passage.first, previous)) return result;
            passage.last = passage.first;
            if (take('-')) {
                if (!location(book, passage.first.verse ? passage.first.chapter : 0, passage.last, passage.first))
                    return result;
                // A range may end with a verse range in the next chapter:
                // Num 12,16–13,1-3a.
                if (passage.last.chapter != passage.first.chapter && passage.last.verse && take('-')) {
                    const Location previousEnd = passage.last;
                    if (!location(book, previousEnd.chapter, passage.last, previousEnd)) return result;
                }
                if (passage.last.chapter < passage.first.chapter ||
                    (passage.last.chapter == passage.first.chapter &&
                     passage.last.verse < passage.first.verse)) return result;
            }
            if (book == BookId::Ps && (peek() == '(' || peek() == '[') &&
                !alternatePsalm(passage.first)) return result;
            result.passages.push_back(passage);
            previous = passage.last;
            if (end()) { result.complete = true; return result; }
            if (take(';')) {
                verseChapter = 0;
                const BookId next = readBook();
                if (next != BookId::Unknown) book = next;
            } else if (take('.') || take(',') || take('+')) {
                if (end() && text_[at_ - 1] == '.') { result.complete = true; return result; }
                verseChapter = passage.last.verse ? passage.last.chapter : 0;
            } else return result;
        } while (!end());
        return result; // A trailing separator is incomplete, not a new passage.
    }

private:
    bool end() const { return at_ == text_.size(); }
    char peek() const { return end() ? '\0' : text_[at_]; }
    bool take(char c) {
        if (peek() != c) return false;
        ++at_;
        return true;
    }
    bool number(unsigned& value) {
        value = 0;
        if (!digit(peek())) return false;
        while (digit(peek())) {
            // Bounded arithmetic: no valid Bible chapter/verse exceeds this.
            if (value > 100) return false;
            value = value * 10 + (text_[at_++] - '0');
        }
        return value > 0 && value <= 1000;
    }
    std::string suffix() {
        const size_t begin = at_;
        while (peek() >= 'a' && peek() <= 'z') ++at_;
        return text_.substr(begin, at_ - begin);
    }
    BookId readBook() {
        const auto language = static_cast<unsigned>(language_);
        if (language >= aliases().size()) return BookId::Unknown;
        BookId result = BookId::Unknown;
        size_t length = 0;
        for (const auto& alias : aliases()[language]) {
            if (alias.first.size() <= length || text_.compare(at_, alias.first.size(), alias.first) != 0)
                continue;
            const size_t after = at_ + alias.first.size();
            if (after != text_.size() && !digit(text_[after]) && text_[after] != '.') continue;
            result = alias.second;
            length = alias.first.size();
        }
        at_ += length;
        if (length) take('.'); // An abbreviation may end in a period.
        return result;
    }
    bool alternatePsalm(Location& out) {
        const char closing = take('(') ? ')' : ']';
        if (closing == ']' && !take('[')) return false;
        if (!number(out.alternatePsalm) || out.alternatePsalm > 150) return false;
        const auto part = suffix();
        if (!part.empty() && part != "a" && part != "b") return false;
        if (!part.empty()) out.alternatePart = part[0];
        return take(closing);
    }
    bool location(BookId book, unsigned verseChapter, Location& out, const Location& previous) {
        if (verseChapter && peek() >= 'a' && peek() <= 'z') {
            out = previous;
            out.suffix = suffix();
            return true;
        }
        out = Location();
        unsigned n;
        if (!number(n)) return false;
        const std::string part = suffix();
        const bool hasAlternate = book == BookId::Ps && !verseChapter && (peek() == '(' || peek() == '[');
        if (hasAlternate && !alternatePsalm(out)) return false;
        if (hasAlternate && (peek() == 'a' || peek() == 'b')) out.psalmPart = text_[at_++];
        if (take(',') || take(':')) {
            out.chapter = n;
            if (!number(out.verse)) return false;
            out.suffix = suffix();
        } else if (verseChapter || chapterCount(book) == 1) {
            out.chapter = verseChapter ? verseChapter : 1;
            out.verse = n;
            out.suffix = part;
        } else {
            out.chapter = n;
        }
        if (book == BookId::Ps && !verseChapter && !part.empty()) {
            if (part != "a" && part != "b") return false;
            out.psalmPart = part[0];
        } else if (!verseChapter && chapterCount(book) != 1 && !part.empty()) return false;
        if (verseChapter && out.chapter == previous.chapter) {
            out.alternatePsalm = previous.alternatePsalm;
            out.psalmPart = previous.psalmPart;
            out.alternatePart = previous.alternatePart;
        }
        return out.chapter <= chapterCount(book);
    }

    const std::string text_;
    Language language_;
    size_t at_ = 0;
};

} // namespace

Language languageFromCode(const std::string& code) {
    if (code == "sk") return Language::Slovak;
    if (code == "cz" || code == "cs" || code == "c2" || code == "czop") return Language::Czech;
    if (code == "la") return Language::Latin;
    if (code == "hu") return Language::Hungarian;
    if (code == "is") return Language::Icelandic;
    if (code == "es") return Language::Spanish;
    if (code == "az") return Language::Azerbaijani;
    if (code == "en") return Language::English;
    return Language::Unknown;
}

const char* bookCode(BookId book) {
    const auto index = static_cast<unsigned>(book);
    return index < static_cast<unsigned>(BookId::Count) ? books[index].code : "";
}

unsigned chapterCount(BookId book) {
    const auto index = static_cast<unsigned>(book);
    return index < static_cast<unsigned>(BookId::Count) ? books[index].chapters : 0;
}

Reference parseReference(const std::string& text, Language language) {
    return Parser(text, language).parse(text);
}

} // namespace bible
