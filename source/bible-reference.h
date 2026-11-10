#ifndef BREVIAR_BIBLE_REFERENCE_H
#define BREVIAR_BIBLE_REFERENCE_H

#include <string>
#include <vector>

namespace bible {

// Independent of the CGI language IDs and of the destination website.
enum class Language { Slovak, Czech, Latin, Hungarian, Icelandic, Spanish, Azerbaijani, English, Unknown };
Language languageFromCode(const std::string& code);

enum class BookId {
    Gen, Exod, Lev, Num, Deut, Josh, Judg, Ruth, Sam1, Sam2,
    Kgs1, Kgs2, Chr1, Chr2, Ezra, Neh, Esth, Job, Ps, Prov,
    Eccl, Song, Isa, Jer, Lam, Ezek, Dan, Hos, Joel, Amos,
    Obad, Jonah, Mic, Nah, Hab, Zeph, Hag, Zech, Mal, Matt,
    Mark, Luke, John, Acts, Rom, Cor1, Cor2, Gal, Eph, Phil,
    Col, Thess1, Thess2, Tim1, Tim2, Titus, Phlm, Heb, Jas, Pet1,
    Pet2, John1, John2, John3, Jude, Rev, Tob, Jdt, Wis, Sir,
    Bar, Macc1, Macc2,
    Count, Unknown
};

const char* bookCode(BookId book);
// Maximum chapter number across the supported citation traditions. Providers
// apply their edition-specific limits (notably Esther and Malachi).
unsigned chapterCount(BookId book);

struct Location {
    unsigned chapter = 0; // Zero means that the chapter is unknown.
    unsigned verse = 0;   // Zero means the whole chapter.
    std::string suffix;
    unsigned alternatePsalm = 0;
    char psalmPart = 0;
    char alternatePart = 0;
};

struct Passage {
    BookId book = BookId::Unknown;
    Location first;
    Location last;
};

struct Reference {
    std::string text; // Original target, including any hidden {r:prefix}.
    BookId book = BookId::Unknown;
    std::vector<Passage> passages;
    bool complete = false;
};

// No global settings, shared scratch buffers, or destructive tokenization.
Reference parseReference(const std::string& text, Language language);

} // namespace bible
#endif
