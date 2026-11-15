#ifndef BREVIAR_PRAYER_SHARING_H
#define BREVIAR_PRAYER_SHARING_H

#include "mysysdef.h"
#include <cstdio>
#include <string>

// Native apps retain their own sharing UI and do not link the QR encoder.
#if defined(BEHAVIOUR_WEB) && !defined(IO_ANDROID) && !defined(__APPLE__)
#define BREVIAR_WEB_SHARING
namespace sharing {

std::string query(const std::string& selection, const std::string& options,
                  const std::string& language, const std::string& calendar);
std::string svg(const std::string& url);

// The backend owns selection/date resolution; the sharing module owns URLs/UI.
extern std::string selection;
extern bool requested;
void menu(FILE* output);
void panel();

} // namespace sharing
#endif
#endif
