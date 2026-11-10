#ifndef BREVIAR_BIBLE_LINKS_H
#define BREVIAR_BIBLE_LINKS_H

#include "bible-reference.h"
#include <memory>
#include <string>

namespace bible {

enum class LinkDetail { None, Text, Book, Chapter, Verse };
struct LinkResult {
    std::string url;
    LinkDetail detail;
    LinkResult(std::string url = "", LinkDetail detail = LinkDetail::None);
};

// Providers know destination URLs, not HTML, rendering flags, or CGI globals.
class BibleLinkProvider {
public:
    virtual ~BibleLinkProvider() = default;
    virtual LinkResult link(const Reference& reference) const = 0;
};

class TextReferenceProvider : public BibleLinkProvider {
public:
    explicit TextReferenceProvider(std::string prefix, bool removeDiacritics = false);
    LinkResult link(const Reference& reference) const override;
private:
    const std::string prefix_;
    const bool removeDiacritics_;
};

class BibleComProvider : public BibleLinkProvider {
public:
    BibleComProvider(std::string baseUrl, std::string edition);
    LinkResult link(const Reference& reference) const override;
private:
    const std::string baseUrl_;
    const std::string edition_;
};

enum class PsalmNumbering { Modern, Traditional };

class NovaVulgataProvider : public BibleLinkProvider {
public:
    static const char* baseUrl();
    explicit NovaVulgataProvider(PsalmNumbering numbering);
    LinkResult link(const Reference& reference) const override;
private:
    const PsalmNumbering numbering_;
};

struct LinkSettings {
    bool useBibleCom = false;
    bool removeDiacritics = false; // Android's DKC Bible-app integration.
    std::string referenceBase;
    std::string bibleComBase;
    std::string bibleComEdition;
};

// A snapshot of the prayer language and configuration, with no retained globals.
class BibleLinks {
public:
    BibleLinks(Language language, const LinkSettings& settings);
    LinkResult link(const std::string& prefix, const std::string& label) const;
private:
    Language language_;
    std::unique_ptr<BibleLinkProvider> provider_;
};

} // namespace bible
#endif
