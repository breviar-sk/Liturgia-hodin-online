// Keep portable C file I/O; opt out of MSVC's CRT deprecation before any headers.
#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "template-reader.h"
#include "common.h"
#include <cerrno>

namespace prayer {

TemplateReader::TemplateReader(const char* path, const char* mode)
    : file_(std::fopen(path, mode), &std::fclose) {
    InitUtf8DecoderState(&decoder_);
}

bool TemplateReader::readCharacter(int& character) {
    while (file_) {
        if (position_ == size_) {
            position_ = 0;
            size_ = std::fread(buffer_.data(), 1, buffer_.size(), file_.get());
            if (size_ == 0) {
                if (std::ferror(file_.get()) && errno == EINTR) {
                    std::clearerr(file_.get());
                    continue;
                }
                return false;
            }
        }
        if (Utf8StreamingDecoder(buffer_[position_++], &decoder_)) {
            character = decoder_.result;
            return true;
        }
    }
    return false;
}

bool TemplateReader::next(Token& token) {
    int character;
    while (readCharacter(character)) {
        if (character == CHAR_KEYWORD_BEGIN) {
            inMarker_ = true;
            marker_.clear();
        } else if (character == CHAR_KEYWORD_END) {
            inMarker_ = false;
            token.kind = Token::Kind::Marker;
            token.text = marker_;
            return true;
        } else if (inMarker_) {
            char bytes[5];
            char* end = bytes;
            EncodeWchar(character, &end);
            marker_.append(bytes, end);
            // Preserve the include reader's recovery for a stray opening brace.
            // Unlike its fixed buffer, appending a multibyte character is safe.
            if (marker_.size() > MAX_BUFFER - 2) {
                inMarker_ = false;
                token.kind = Token::Kind::Recovery;
                token.text = marker_;
                marker_.clear();
                return true;
            }
        } else {
            token.kind = Token::Kind::Character;
            token.character = character;
            return true;
        }
    }
    return false;
}

Marker::Marker(const std::string& text) {
    // Match splitword(): trim leading ASCII spaces, split at the first colon,
    // then trim leading spaces in the argument. Preserve trailing spaces.
    const auto begin = text.find_first_not_of(' ');
    if (begin == std::string::npos) return;
    const auto colon = text.find(':', begin);
    name = text.substr(begin, colon == std::string::npos ? colon : colon - begin);
    if (colon != std::string::npos) {
        const auto value = text.find_first_not_of(' ', colon + 1);
        if (value != std::string::npos) argument = text.substr(value);
    }
}

} // namespace prayer
