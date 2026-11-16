#include "prayer-sharing.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    const auto dated = sharing::query("p=mv&r=2026&m=11&qt=pdt&d=13", "&amp;o1=7&amp;f=Noto Serif", "cz", "");
    assert(dated == "qt=pdt&d=13&m=11&r=2026&p=mv&j=cz&k=&f=Noto%20Serif&o1=7&sh=1");
    assert(sharing::query("qt=pst&st=2&p=mk", "c=1", "sk", "") == "qt=pst&p=mk&j=sk&k=&c=1&sh=1&st=2");
    assert(sharing::query("qt=pdnes&share=1", "dl=hu&sh=99", "sk", "") == "qt=pdnes&j=sk&k=&sh=1");
    assert(sharing::query("qt=plo&r=2026&lo=3", "", "la", "op") == "qt=plo&r=2026&j=la&k=op&lo=3&sh=1");
    assert(sharing::query("qt=pdnes", "f=A+B% C", "sk", "").find("f=A%2BB%25%20C") != std::string::npos);
    assert(sharing::withFragment("https://example.test/?a=1", "") == "https://example.test/?a=1");
    assert(sharing::withFragment("https://example.test/", "sms") == "https://example.test/#sms");
    assert(sharing::withFragment("https://example.test/", "a%20b+%2520") == "https://example.test/#a%20b%2B%2520");
    assert(sharing::withFragment("https://example.test/", "žalm &?#%broken") == "https://example.test/#%C5%BEalm%20%26%3F%23%25broken");
    try {
        sharing::query("qt=pdnes", "f=" + std::string(2000, 'x'), "sk", "");
        assert(false);
    } catch (const std::length_error&) {}
    const auto image = sharing::svg("https://breviar.sk/cgi-bin/l.cgi?" + dated);
    assert(image.find("<svg ") == 0);
    assert(image.find("fill=\"#FFFFFF\"") != std::string::npos);
    assert(image.find("fill=\"#000000\"") != std::string::npos);
    assert(image.find("https:") == std::string::npos); // Payload is encoded, never interpolated into SVG.
    try {
        sharing::svg(std::string(10000, 'x'));
        assert(false);
    } catch (const std::length_error&) {}
    std::cout << "Prayer sharing query and QR tests passed\n";
}
