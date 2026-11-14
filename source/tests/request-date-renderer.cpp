// Run the actual renderer with a controlled clock, without production clock hooks.
#include "breviar.h"
#include "myexpt.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

static time_t timestamp;
extern "C" time_t time(time_t* output) noexcept {
    if (output) *output = timestamp;
    return timestamp;
}

int main(int argc, char** argv) {
    if (argc != 3) return 2;
    timestamp = static_cast<time_t>(std::strtoll(argv[1], nullptr, 10));
    setenv("TZ", "UTC", 1);
    tzset();
    setenv("REQUEST_METHOD", "GET", 1);
    setenv("QUERY_STRING", argv[2], 1);
    const char* arguments[] = {"breviar.cgi", nullptr};
    breviar_main(1, arguments);
    std::cout << getExportedString();
}
