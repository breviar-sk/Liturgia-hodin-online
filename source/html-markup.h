#ifndef BREVIAR_HTML_MARKUP_H
#define BREVIAR_HTML_MARKUP_H

#include <string>

namespace prayer {

std::string escapeHtmlAttribute(const std::string& value);

// Track literal HTML independently of prayer markers. Text substitutions must
// never change attribute values (URLs, classes, IDs, or inline CSS).
class HtmlMarkup {
public:
    bool consume(int character);
private:
    enum class State { Text, Opening, Tag, SingleQuote, DoubleQuote };
    State state_ = State::Text;
};

} // namespace prayer
#endif
