#ifndef BREVIAR_PRAYER_RENDERER_H
#define BREVIAR_PRAYER_RENDERER_H

#include "common.h"
#include <string>

namespace prayer {

// One instance per rendered prayer. Included sections share only this state;
// their parsing/capture state belongs to the individual section renderer.
struct RenderState {
    int skipDepth = 0;
    bool skipEasterReading = false;
    bool inVigil = false;
    int doxologyCount = 0;
    int antiphonCount = 0;
    bool invitatoryCross = false;
    std::string crossAnchor;
    std::string ending;
};

enum class SectionResult { Rendered, Skipped, FileNotFound, SectionNotFound, ReadError };

SectionResult renderSection(RenderState& state, short type, short prayer, const char* part,
                            const char* path, const char* anchor, bool reportErrors = true);

} // namespace prayer

// Existing entry points used by prayer rendering and standalone information pages.
void includeFile(short type, short prayer, const char* part, const char* path, const char* anchor);
void interpretTemplate(short type, short prayer, char* path, short navigation = ANO);
void export_div_to_continue_tts_voice_output(short exportComment = ANO);
void export_tts_pause(short pauseType = TTS_PAUSE);

#endif
