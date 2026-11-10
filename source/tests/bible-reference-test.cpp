#include "bible-reference.h"
#include "bible-links.h"
#include <cstdlib>
#include <iostream>
#include <utility>

using namespace bible;

static void check(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(1); }
}

int main(int argc, char** argv) {
    if (argc == 2 && std::string(argv[1]) == "--vatican-links") {
        const NovaVulgataProvider provider(PsalmNumbering::Modern);
        for (unsigned i = 0; i < static_cast<unsigned>(BookId::Count); ++i) {
            const auto book = static_cast<BookId>(i);
            Reference ref;
            ref.book = book;
            Passage passage;
            passage.book = book;
            ref.passages.push_back(passage);
            for (unsigned chapter = 1; chapter <= chapterCount(book); ++chapter) {
                ref.passages[0].first.chapter = chapter;
                std::cout << bookCode(book) << '\t' << chapter << '\t' << provider.link(ref).url << '\n';
            }
        }
        return 0;
    }
    if (argc == 3 && std::string(argv[1]) == "--parse") {
        std::string text;
        while (std::getline(std::cin, text)) {
            const auto ref = parseReference(text, languageFromCode(argv[2]));
            std::cout << bookCode(ref.book) << '\t' << ref.complete << '\t'
                      << (ref.passages.empty() ? 0 : ref.passages.front().first.chapter) << '\n';
        }
        return 0;
    }
    for (const auto& text : {"Eph 4, 1-6", "Eph_4,1–6", "EPH\u00a04, 1—6", "Eph.&nbsp;4,1-6"}) {
        const auto ref = parseReference(text, Language::Latin);
        check(ref.complete && ref.book == BookId::Eph && ref.passages.size() == 1,
              "Latin book or whitespace not recognized");
        check(ref.passages[0].first.chapter == 4 && ref.passages[0].first.verse == 1 &&
              ref.passages[0].last.verse == 6, "Verse range not preserved");
        check(ref.text == text, "Original reference was modified");
    }
    for (const auto& language : {"sk", "cz", "c2", "hu", "la", "is", "es", "az"}) {
        const auto ref = parseReference("Mt 5, 1-12", languageFromCode(language));
        check(ref.complete && ref.book == BookId::Matt, "Language profile failed");
    }
    const auto cor = parseReference("1 Cor 13, 1-3. 8; 14, 1; Lc 1, 46-55", Language::Latin);
    check(cor.complete && cor.passages.size() == 4, "Lists and multiple chapters/books failed");
    check(cor.passages[1].first.verse == 8 && cor.passages[2].first.chapter == 14 &&
          cor.passages[3].book == BookId::Luke, "List context was lost");
    const auto ps = parseReference("Ps 113 B (115), 1-9", Language::Latin);
    check(ps.complete && ps.passages[0].first.chapter == 113 &&
          ps.passages[0].first.psalmPart == 'b' && ps.passages[0].first.alternatePsalm == 115,
          "Psalm numbering was discarded");
    const auto psPart = parseReference("Ps 114 (116 A)", Language::Latin);
    check(psPart.complete && psPart.passages[0].first.alternatePart == 'a', "Alternate Psalm part lost");
    const auto jude = parseReference("Iud 1-8. 12-13. 17-25", Language::Latin);
    check(jude.complete && jude.passages.size() == 3 && jude.passages[0].first.chapter == 1 &&
          jude.passages[2].last.verse == 25, "Single-chapter book failed");
    check(parseReference("Ps 147, 12-20 (147 B)", Language::Latin).complete,
          "Trailing Psalm alternate number failed");
    check(parseReference("Est 4, 17m-17kk", Language::Latin).complete,
          "Esther's verse suffixes failed");
    check(parseReference("Num 12, 16 – 13, 1-3a. 17-33", Language::Latin).complete,
          "Cross-chapter range with a final verse range failed");
    check(parseReference("Ps 29, 2+4. 5-6. 11+12a+13b", Language::Latin).complete,
          "Plus-separated verse list failed");
    check(parseReference("SS 9, 10", Language::Icelandic).book == BookId::Wis &&
          parseReference("Ss 9, 10", Language::Icelandic).book == BookId::Wis,
          "Icelandic Wisdom alias confused with Song of Songs");
    check(parseReference("Sk 4, 12", Language::Icelandic).book == BookId::Unknown,
          "Ambiguous translated/untranslated book alias guessed a book");
    const auto verse = parseReference("Lc 1, 46b-55a", Language::Latin);
    check(verse.complete && verse.passages[0].first.suffix == "b" && verse.passages[0].last.suffix == "a",
          "Verse suffixes lost");
    const auto cross = parseReference("Io 3, 16-4, 2", Language::Latin);
    check(cross.complete && cross.passages[0].last.chapter == 4 && cross.passages[0].last.verse == 2,
          "Cross-chapter range failed");
    for (const auto& text : {"", "GS 43", "Eph 999999999999999999999, 1", "Eph 0, 1", "Eph 4, 6-1",
                             "Eph 4,", "Ps 113 (999)", "Eph 4, 1;", "1 "}) {
        check(!parseReference(text, Language::Latin).complete, "Malformed reference was accepted");
    }
    check(parseReference(std::string(100000, 'x'), Language::Latin).book == BookId::Unknown,
          "Long input guessed a Bible book");
    check(!parseReference("Eph 4", Language::Unknown).complete, "Unknown language guessed a book");
    for (const auto& text : {"\x80", "\xC2", "\xE2\x82", "\xFF"})
        check(!parseReference(text, Language::Latin).complete, "Invalid UTF-8 guessed a reference");
    const BibleComProvider bibleCom("https://www.bible.com/bible/", "823");
    check(bibleCom.link(parseReference("Eph 4, 1-6", Language::Latin)).url ==
          "https://www.bible.com/bible/823/EPH.4.1-6", "Bible.com Latin alias failed");
    check(bibleCom.link(cor).url == "https://www.bible.com/bible/823/1CO.13.1-3,8",
          "Bible.com verse list failed");
    check(bibleCom.link(parseReference("LG 63", Language::Latin)).url.empty(),
          "Church document was linked to the Bible");
    check(BibleComProvider("https://www.bible.com/bible/", "ru_text").link(cor).url.empty(),
          "Configuration placeholder became an edition ID");
    const TextReferenceProvider textProvider("https://example.org/?source=custom&in=");
    check(textProvider.link(parseReference("Ž 95, 1&x=2", Language::Slovak)).url ==
          "https://example.org/?source=custom&in=%C5%BD%2095%2C%201%26x%3D2",
          "Citation escaped its query parameter");
    check(TextReferenceProvider("https://dkc.kbs.sk/dkc.php?in=", true)
          .link(parseReference("Ž 95", Language::Slovak)).url == "https://dkc.kbs.sk/dkc.php?in=Z%2095",
          "Android Bible-app normalization changed");
    LinkSettings settings;
    settings.referenceBase = "https://custom.example/";
    const BibleLinks custom(Language::Latin, settings);
    check(custom.link("Eph 4,", "1-6").url == "https://custom.example/Eph%204%2C%201-6",
          "Custom reference prefix was ignored");
    settings.useBibleCom = true;
    settings.bibleComBase = "https://www.bible.com/bible/";
    settings.bibleComEdition = "163";
    check(BibleLinks(Language::Slovak, settings).link("Lk", "1, 46-55").url ==
          "https://www.bible.com/bible/163/LUK.1.46-55", "Provider selection or hidden prefix failed");
    const NovaVulgataProvider vulgate(PsalmNumbering::Traditional);
    const std::string vatican = NovaVulgataProvider::baseUrl();
    check(vulgate.link(parseReference("Eph 4, 1-6", Language::Latin)).url ==
          vatican + "nova-vulgata_nt_epist-ephesios_lt.html#4", "Vatican Ephesians link failed");
    check(vulgate.link(parseReference("Lc 1, 46-55", Language::Latin)).url ==
          vatican + "nova-vulgata_nt_evang-lucam_lt.html#1", "Magnificat link failed");
    for (const auto& example : {std::make_pair("Ps 50 (51), 3-21", "51"),
                               std::make_pair("Ps 94, 1-7", "95"),
                               std::make_pair("Ps 9 A (9)", "9"),
                               std::make_pair("Ps 9 B", "10"),
                               std::make_pair("Ps 113 B (115)", "115"),
                               std::make_pair("Ps 114 (116 A)", "116"),
                               std::make_pair("Ps 115 (116 B)", "116"),
                               std::make_pair("Ps 146 (147 A)", "147"),
                               std::make_pair("Ps 147 (147 B)", "147"),
                               std::make_pair("Ps 150", "150")}) {
        check(vulgate.link(parseReference(example.first, Language::Latin)).url ==
              vatican + "nova-vulgata_vt_psalmorum_lt.html#PSALMUS%20" + example.second,
              "Traditional Psalm number mapped to the wrong anchor");
    }
    for (const char* text : {"Ps 9", "Ps 113", "Ps 50 (52)", "Ps 113 B (114)"})
        check(vulgate.link(parseReference(text, Language::Latin)).detail == LinkDetail::Book,
              "Ambiguous or inconsistent Psalm number guessed an anchor");
    check(NovaVulgataProvider(PsalmNumbering::Modern)
          .link(parseReference("Ž 95 (94)", Language::Slovak)).url ==
          vatican + "nova-vulgata_vt_psalmorum_lt.html#PSALMUS%2095", "Modern numbering changed");
    check(vulgate.link(jude).url == vatican + "nova-vulgata_nt_epist-iudae_lt.html",
          "Single-chapter book acquired a nonexistent anchor");
    for (const char* text : {"Est 13, 1", "Mal 4, 1", "Eph 99999999999999, 1"})
        check(vulgate.link(parseReference(text, Language::Latin)).detail == LinkDetail::Book,
              "Unsupported chapter acquired a nonexistent anchor");
    check(vulgate.link(parseReference("GS 43", Language::Latin)).url.empty(),
          "Unknown book acquired a Vatican link");
    settings.useBibleCom = false;
    settings.referenceBase = vatican;
    check(BibleLinks(Language::Latin, settings).link("Eph", "4, 1-6").url ==
          vatican + "nova-vulgata_nt_epist-ephesios_lt.html#4", "Latin default did not select Vatican");
    settings.useBibleCom = true;
    check(BibleLinks(Language::Latin, settings).link("Eph", "4, 1-6").url ==
          "https://www.bible.com/bible/163/EPH.4.1-6", "Vatican overrode explicit Bible.com choice");
    std::cout << "Bible reference parser tests passed\n";
}
