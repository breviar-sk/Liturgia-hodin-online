#include "html-markup.h"

namespace prayer {

std::string escapeHtmlAttribute(const std::string& value) {
    std::string result;
    for (char c : value) {
        switch (c) {
        case '&': result += "&amp;"; break;
        case '"': result += "&quot;"; break;
        case '\'': result += "&#39;"; break;
        case '<': result += "&lt;"; break;
        case '>': result += "&gt;"; break;
        default: result += c;
        }
    }
    return result;
}

bool HtmlMarkup::consume(int c) {
    switch (state_) {
    case State::Text:
        if (c == '<') state_ = State::Opening;
        return false;
    case State::Opening:
        // Comments contain prayer markers and retain their historical text
        // formatting. Only actual tags enter the attribute-preserving state.
        state_ = ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '/')
            ? State::Tag : State::Text;
        return state_ == State::Tag;
    case State::Tag:
        if (c == '\'') state_ = State::SingleQuote;
        else if (c == '"') state_ = State::DoubleQuote;
        else if (c == '>') state_ = State::Text;
        return true;
    case State::SingleQuote:
        if (c == '\'') state_ = State::Tag;
        return true;
    case State::DoubleQuote:
        if (c == '"') state_ = State::Tag;
        return true;
    }
    return false;
}

} // namespace prayer
