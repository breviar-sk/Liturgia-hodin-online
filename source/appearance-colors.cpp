#include "appearance-colors.h"
#include "mydefs.h"

namespace appearance {
namespace {

std::array<ColorSetting, 6> settings = {{
	{Mode::Day, Role::Text, "ct0", "--prayer-text", ""},
	{Mode::Day, Role::Rubric, "cr0", "--prayer-rubric", ""},
	{Mode::Day, Role::Background, STR_THEME_LIGHT_BACKGROUND_COLOR, "--prayer-background", ""},
	{Mode::Night, Role::Text, "ct1", "--prayer-text", ""},
	{Mode::Night, Role::Rubric, "cr1", "--prayer-rubric", ""},
	{Mode::Night, Role::Background, STR_THEME_DARK_BACKGROUND_COLOR, "--prayer-background", ""},
}};

} // namespace

const std::array<ColorSetting, 6>& colors() { return settings; }

void resetColors() {
	for (auto& setting : settings) setting.value.clear();
}

std::string normalizeColor(const std::string& value) {
	if (value.size() != 3 && value.size() != 6) return "";
	std::string result;
	for (char c : value) {
		if (c >= 'A' && c <= 'F') c += 'a' - 'A';
		if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return "";
		result += c;
		if (value.size() == 3) result += c;
	}
	return result;
}

void setColor(const std::string& parameter, const std::string& value) {
	for (auto& setting : settings) {
		if (parameter == setting.parameter) {
			setting.value = normalizeColor(value);
			return;
		}
	}
}

const ColorSetting& color(Mode mode, Role role) {
	// The catalogue contains every combination of the two enums.
	return settings[static_cast<unsigned>(mode) * 3 + static_cast<unsigned>(role)];
}

std::string colorStyle(Mode mode) {
	std::string result;
	for (const auto& setting : settings) {
		if (setting.mode == mode && !setting.value.empty()) {
			result += std::string(setting.property) + ": #" + setting.value + "; ";
		}
	}
	return result;
}

} // namespace appearance
