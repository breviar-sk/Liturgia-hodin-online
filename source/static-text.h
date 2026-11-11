#ifndef BREVIAR_STATIC_TEXT_H
#define BREVIAR_STATIC_TEXT_H

#include <string>

namespace prayer {

struct RenderState;

struct StaticPage {
    const char* file = "";
    const char* anchor = "";
};

// Only the main offices have an Ordinary; all other values default to Lauds.
short ordinariumPrayer(short prayer);

// Named, allowlisted sections: never accept a filename from a URL.
StaticPage staticPage(const std::string& name);

// {link:psalm-95}label{/link}, {link:ordinarium-mrch#fragment}label{/link}, etc.
// Resolve semantic template links using the current language and reader options.
// An unavailable target returns an empty URL, leaving its label readable.
std::string contentLink(const std::string& target);

void renderStaticPage(RenderState& state, short type, short prayer, const char* part,
                      const char* path, const char* anchor);

} // namespace prayer
#endif
