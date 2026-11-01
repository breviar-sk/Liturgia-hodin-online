#ifndef BREVIAR_XML_SETTINGS_H
#define BREVIAR_XML_SETTINGS_H

// Display-only language for this request; JAZYK_UNDEF keeps the prayer language.
extern short int _device_language;

// XML captions: device language, English, then prayer language. Choice labels
// additionally preserve missing prayer-language entries (availability metadata).
const char* xml_settings_label(const char* const* labels);
const char* xml_settings_choice_label(const char* const* labels);

// Uses the current renderer settings snapshot and the active Export() stream.
// Like the rest of the renderer, callers must serialize access to global state.
void xml_export_options_and_menu();

#endif
