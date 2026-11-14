#include "appearance-colors.h"

#include <cassert>
#include <iostream>

int main() {
	using namespace appearance;
	assert(normalizeColor("AbC") == "aabbcc");
	assert(normalizeColor("12AbEf") == "12abef");
	for (const auto& invalid : {"", "1", "1234", "gggggg", "#ffffff", "fff;bad"}) {
		assert(normalizeColor(invalid).empty());
	}

	setColor("ct0", "ABC");
	setColor("cr0", "fed");
	setColor("c0", "ffffcc");
	setColor("ct1", "ffffff");
	setColor("cr1", "ffff00");
	setColor("c1", "000000");
	assert(color(Mode::Day, Role::Text).value == "aabbcc");
	assert(color(Mode::Night, Role::Background).value == "000000");
	assert(colorStyle(Mode::Day).find("--prayer-rubric: #ffeedd;") != std::string::npos);
	assert(colorStyle(Mode::Day).find("#000000") == std::string::npos);
	setColor("ct0", "");
	assert(colorStyle(Mode::Day).find("--prayer-text") == std::string::npos);
	assert(color(Mode::Night, Role::Text).value == "ffffff");
	setColor("ct1", "not-hex");
	assert(color(Mode::Night, Role::Text).value.empty());
	resetColors();
	for (const auto& setting : colors()) assert(setting.value.empty());
	assert(colorStyle(Mode::Day).empty());
	assert(colorStyle(Mode::Night).empty());
	std::cout << "Appearance colors tests passed\n";
}
