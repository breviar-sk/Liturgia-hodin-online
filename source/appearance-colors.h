#ifndef BREVIAR_APPEARANCE_COLORS_H
#define BREVIAR_APPEARANCE_COLORS_H

#include <array>
#include <string>

namespace appearance {

enum class Mode { Day, Night };
enum class Role { Text, Rubric, Background };

struct ColorSetting {
	Mode mode;
	Role role;
	const char* parameter;
	const char* property;
	std::string value; // Empty means the original stylesheet color.
};

// Request-local state, reset at the same boundary as the other renderer options.
const std::array<ColorSetting, 6>& colors();
void resetColors();
void setColor(const std::string& parameter, const std::string& value);
const ColorSetting& color(Mode mode, Role role);
std::string normalizeColor(const std::string& value);
std::string colorStyle(Mode mode);

} // namespace appearance

#endif
