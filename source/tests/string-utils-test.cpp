#include "mystring.h"
#include "utf8-utils.h"

#include <stdlib.h>

static char scratch[MAX_STR];
char* _global_pom_str = scratch;
short int _global_override_thin_nbsp = 0;

#define CHECK(condition) do { \
	if (!(condition)) { \
		fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition); \
		exit(1); \
	} \
} while (0)

static void test_case_conversion() {
	CHECK(mystr_first_upper(NULL).empty());
	CHECK(mystr_first_lower("").empty());
	CHECK(mystr_first_upper("abc DEF") == "Abc DEF");
	CHECK(mystr_first_lower("ABC def") == "aBC def");
	CHECK(mystr_first_upper("\xC4\xBE\xC5\xA1\xC4\x8D") == "\xC4\xBD\xC5\xA1\xC4\x8D"); // ľšč -> Ľšč
	CHECK(mystr_first_lower("\xC3\x9Avod") == "\xC3\xBAvod"); // Úvod -> úvod
	CHECK(mystr_first_upper("\xC5\x91sz") == "\xC5\x90sz"); // Hungarian ő
	CHECK(mystr_first_upper("\xC3\xBEing") == "\xC3\x9Eing"); // Icelandic þ
	CHECK(mystr_first_upper("\xCE\xB1 text") == "\xCE\x91 text"); // Greek α
	CHECK(mystr_first_upper("\xD1\x8F text") == "\xD0\xAF text"); // Cyrillic я
	CHECK(mystr_first_upper("\xC4\xB1 text") == "I text"); // Dotless i: byte length changes
	CHECK(mystr_first_upper("\xF0\x9F\x99\x82 text") == "\xF0\x9F\x99\x82 text");
	CHECK(mystr_first_upper("7 text") == "7 text");

	const char* invalid[] = {"\x80", "\xC0\xAF", "\xC2", "\xE2\x82", "\xF0\x9F\x99",
		"\xE0\x80\x80", "\xED\xA0\x80", "\xF0\x80\x80\x80", "\xF4\x90\x80\x80", "\xFF"};
	for (size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
		// Exact-sized allocations let ASan detect reads beyond a truncated sequence.
		const size_t size = strlen(invalid[i]) + 1;
		char* text = static_cast<char*>(malloc(size));
		CHECK(text != NULL);
		memcpy(text, invalid[i], size);
		CHECK(mystr_first_upper(text) == text);
		CHECK(mystr_first_lower(text) == text);
		free(text);
	}
	CHECK(mystr_first_upper("a\xFF") == "A\xFF"); // Leave the rest of the bytes alone.
}

static void test_buffers() {
	struct Guarded { char text[8]; char guard[5]; } buffer = {{0}, "keep"};
	CHECK(mysnprintf(buffer.text, "%s:%d", "abc", 12) == 6);
	CHECK(strcmp(buffer.text, "abc:12") == 0);
	CHECK(mysnprintf(buffer.text, "%s", "1234567") == 7);
	CHECK(strcmp(buffer.text, "1234567") == 0);
	CHECK(mysnprintf(buffer.text, "%s", "123456789") == 9);
	CHECK(strcmp(buffer.text, "1234567") == 0);
	CHECK(strcmp(buffer.guard, "keep") == 0);
	char single[1] = {'x'};
	CHECK(mysnprintf(single, "%s", "long") == 4);
	CHECK(single[0] == '\0');

	mystrcpy(buffer.text, "ABCDEFGHIJK", sizeof(buffer.text));
	CHECK(strcmp(buffer.text, "ABCDEFG") == 0);
	CHECK(strcmp(buffer.guard, "keep") == 0);
	mystrcpy(buffer.text, "ignored", 0);
	mystrcpy(buffer.text, "ignored", -1);
	CHECK(strcmp(buffer.text, "ABCDEFG") == 0);
	mystrcpy(single, "long", sizeof(single));
	CHECK(single[0] == '\0');

	char title[] = "\xC4\xBD\xC5\xA1\xC4\x8D";
	FirstToLower(title, sizeof(title));
	CHECK(strcmp(title, "\xC4\xBE\xC5\xA1\xC4\x8D") == 0);
	char empty[1] = {0};
	FirstToLower(empty, sizeof(empty));
	CHECK(empty[0] == '\0');
	FirstToLower(NULL, 0);
	FirstToLower(single, 0);
	char clipped[] = "ABC";
	FirstToLower(clipped, 2);
	CHECK(strcmp(clipped, "a") == 0);
	CHECK(clipped[2] == 'C');

	char text[] = "abc", prefix[] = "ab", absent[] = "bc", longer[] = "abcdef";
	CHECK(startsWith(text, prefix));
	CHECK(!startsWith(text, absent));
	CHECK(!startsWith(text, longer));
	CHECK(startsWith(text, empty));
}

static void test_colors() {
	char valid[][8] = {"000", "fff", "ABC", "aB9", "012345", "aBcDeF"};
	for (size_t i = 0; i < sizeof(valid) / sizeof(valid[0]); ++i) CHECK(isValidHexaCode(valid[i]));
	char invalid[][9] = {"", "ab", "abcd", "12345", "1234567", "xyz", "FFG", "#fff", "12 ", "12;", "ab\""};
	for (size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) CHECK(!isValidHexaCode(invalid[i]));
	CHECK(!isValidHexaCode(NULL));
	for (int c = 1; c <= 255; ++c) {
		char color[] = {'0', static_cast<char>(c), '0', '\0'};
		const bool hex = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
		CHECK(isValidHexaCode(color) == hex);
	}
}

int main() {
	test_case_conversion();
	test_buffers();
	test_colors();
	puts("String utility tests passed");
	return 0;
}
