#ifndef BREVIAR_XML_SETTINGS_H
#define BREVIAR_XML_SETTINGS_H

// Uses the current renderer settings snapshot and the active Export() stream.
// Like the rest of the renderer, callers must serialize access to global state.
void xml_export_options_and_menu();

#endif
