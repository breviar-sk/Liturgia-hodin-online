#ifndef BREVIAR_PRAYER_MARKUP_H
#define BREVIAR_PRAYER_MARKUP_H

#include "template-reader.h"
#include <string>
#include <vector>

namespace prayer {

// Templates historically use slightly different CSS/pause spacing than includes.
enum class MarkupStyle { Template, Section };

// Inline markup owns its captures and visibility. Closing a reference or a verse
// cannot enable text hidden by an enclosing section or optional passage.
class InlineMarkup {
public:
    explicit InlineMarkup(MarkupStyle style) : style_(style) {}
    bool marker(const Marker& marker, bool visible);
    void character(int character, bool visible);
    void recovery(const std::string& text, bool visible);
    bool visible(bool parentVisible) const;

private:
    enum class Kind { Reference, FootnoteReference, Catechesis, Psalm95,
                      Footnote, Note, Verse, Italics, FullText };
    struct Frame {
        Kind kind;
        bool enabled;
        std::string argument;
        std::string text;
        std::string closing;
    };
    void open(Kind kind, bool enabled, const std::string& argument = "",
              const std::string& opening = "", const std::string& closing = "");
    void close(Kind kind, bool parentVisible);
    void emit(const std::string& html);
    bool symbol(const std::string& name, bool enabled);
    MarkupStyle style_;
    std::vector<Frame> frames_;
};

} // namespace prayer
#endif
