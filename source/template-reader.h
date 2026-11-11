#ifndef BREVIAR_TEMPLATE_READER_H
#define BREVIAR_TEMPLATE_READER_H

#include "utf8-utils.h"
#include <array>
#include <cstdio>
#include <memory>
#include <string>

namespace prayer {

struct Token {
    enum class Kind { Character, Marker, Recovery };
    Kind kind = Kind::Character;
    int character = 0;
    std::string text;
};

// The syntax is deliberately independent of HTML: markers can occur inside
// comments, and comments can span several markers and ordinary text.
class TemplateReader {
public:
    TemplateReader(const char* path, const char* mode);
    bool isOpen() const { return file_ != nullptr; }
    bool next(Token& token);
    bool failed() const { return failed_; }

private:
    bool readCharacter(int& character);
    std::unique_ptr<FILE, int (*)(FILE*)> file_;
    std::array<char, 4096> buffer_;
    std::size_t position_ = 0;
    std::size_t size_ = 0;
    Utf8DecoderState decoder_;
    bool inMarker_ = false;
    bool failed_ = false;
    std::string marker_;
};

struct Marker {
    explicit Marker(const std::string& text);
    std::string name;
    std::string argument;
};

} // namespace prayer
#endif
