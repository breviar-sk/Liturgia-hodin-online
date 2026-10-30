// Exercise the same in-memory Export() path used by iOS. A long translation
// makes the old 16-bit per-write length limit reproducible on a Linux build.
#include "breviar.h"
#include "myexpt.h"
#include "settings-text.h"
#include "xml-settings.h"

#include <cassert>
#include <iostream>
#include <string>

int main() {
	_global_jazyk = JAZYK_SK;
	const char* original = html_text_Jazyk[JAZYK_SK];
	const std::string prefix = "Long label " + std::string(40000, 'x');
	const std::string label = prefix + " & <\"'> €";
	html_text_Jazyk[JAZYK_SK] = label.c_str();
	initExport();
	xml_export_options_and_menu();
	const std::string xml = getExportedString();
	closeExport();
	html_text_Jazyk[JAZYK_SK] = original;
	assert(xml.find(prefix + " &amp; &lt;&quot;&apos;&gt; €") != std::string::npos);
	assert(xml.find("<Menu Version=\"1\">") == 0);
	assert(xml.find("</Menu>\n<Options>\n") != std::string::npos);
	assert(xml.substr(xml.size() - 11) == "</Options>\n");

	// Export again in the same process: labels and effective state must come
	// from the current request, not a cached tree from the preceding request.
	_global_jazyk = JAZYK_CZ;
	_global_opt[OPT_0_SPECIALNE] = BIT_OPT_0_VERSE;
	initExport();
	xml_export_options_and_menu();
	const std::string next = getExportedString();
	closeExport();
	assert(next.find("Long label ") == std::string::npos);
	assert(next.find("Key=\"prayers.alternatives.cz-hymn-selection\"") != std::string::npos);
	assert(next.find(">1</BitOpt0VerseNumbers>") != std::string::npos);
	std::cout << "Settings XML in-memory export tests passed\n";
}
