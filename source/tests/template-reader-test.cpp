#include "template-reader.h"
#include "common.h"
#include <cassert>
#include <fstream>
#include <iostream>

// Storage required by the legacy UTF-8/string helpers linked into this test.
static char scratch[MAX_STR];
char* _global_pom_str = scratch;
short int _global_override_thin_nbsp = 0;

int main() {
    // Split a UTF-8 character across the reader's 4096-byte input boundary.
    const char* path = ".test-build/reader-input.htm";
    const std::string text = std::string(4095, 'a') + "ž{r:Ž}1{/r}†";
    { std::ofstream(path, std::ios::binary) << text; }
    prayer::TemplateReader reader(path, "rb");
    assert(reader.isOpen());
    prayer::Token token;
    std::string roundTrip;
    while (reader.next(token)) {
        if (token.kind == prayer::Token::Kind::Marker) {
            roundTrip += "{" + token.text + "}";
        } else {
            assert(token.kind == prayer::Token::Kind::Character);
            char bytes[5];
            char* end = bytes;
            EncodeWchar(token.character, &end);
            roundTrip.append(bytes, end);
        }
    }
    assert(roundTrip == text);
    assert(!reader.failed());
    const prayer::Marker marker("  r:  Ž 102, ");
    assert(marker.name == "r" && marker.argument == "Ž 102, ");
    const prayer::Marker url("k:https://example.org/text");
    assert(url.argument == "https://example.org/text");

    { std::ofstream(path) << "{" << std::string(255, 'x') << "tail{unfinished"; }
    prayer::TemplateReader broken(path, "rb");
    assert(broken.next(token) && token.kind == prayer::Token::Kind::Recovery);
    assert(token.text == std::string(255, 'x'));
    for (char c : std::string("tail")) {
        assert(broken.next(token) && token.kind == prayer::Token::Kind::Character);
        assert(token.character == c);
    }
    assert(!broken.next(token)); // Legacy behavior: discard an unfinished marker at EOF.
    prayer::TemplateReader missing(".test-build/no-such-template.htm", "rb");
    assert(!missing.isOpen() && !missing.next(token));
#if !defined(_WIN32)
    // POSIX permits opening a directory; reading it must not look like clean EOF.
    prayer::TemplateReader directory(".", "rb");
    assert(directory.isOpen());
    assert(!directory.next(token) && directory.failed());
#endif
    std::cout << "Template reader tests passed\n";
}
