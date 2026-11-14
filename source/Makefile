-include config.mk

CXXFLAGS ?= -Wall -W -DMODEL_SELECTED_IN_MAKEFILE -DMODEL_linux_citania -Wno-unknown-pragmas
TARGET ?= ../l.cgi

SRCS = \
	breviar.cpp  \
	liturgia.cpp \
	mygetopt.cpp \
	mylog.cpp    \
	myhpage.cpp  \
	myexpt.cpp   \
	cgiutils.cpp \
	myconf.cpp   \
	mydefs.cpp   \
	mystring.cpp \
	citania.cpp  \
	dbzaltar.cpp \
	kalendar.cpp \
	utf8-utils.cpp \
	xml-settings.cpp \
	template-reader.cpp \
	prayer-renderer.cpp \
	prayer-markup.cpp \
	html-markup.cpp \
	static-text.cpp \
	bible-reference.cpp \
	bible-links.cpp \
	appearance-colors.cpp

OBJS = $(subst cpp,o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

depend: $(SRCS)
	$(CXX) -MM $(CXXFLAGS) $^ >.depend

citania-merged.cpp: citania-gen.cpp citania-manual.cpp
	export LC_ALL=C; cat citania-manual.cpp citania-gen.cpp | sort -t \" -s -u -k 1,2 >citania-merged.cpp

citania.o: citania.cpp citania-merged.cpp

breviar-no-main.o: breviar.o
	objcopy --localize-symbol=main breviar.o breviar-no-main.o

print_codes: print_codes.o breviar-no-main.o citania.o dbzaltar.o kalendar.o liturgia.o \
             mygetopt.o mylog.o myhpage.o myexpt.o cgiutils.o myconf.o utf8-utils.o \
             mydefs.o mystring.o xml-settings.o template-reader.o prayer-renderer.o prayer-markup.o html-markup.o static-text.o bible-reference.o bible-links.o appearance-colors.o
	g++ -o $@ $^

clean:
	rm -f $(TARGET) *.o .depend

TEST_DIR ?= .test-build

$(TEST_DIR)/string-utils-test: tests/string-utils-test.cpp mystring.cpp mystring.h utf8-utils.cpp utf8-utils.h common.h
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -I. tests/string-utils-test.cpp mystring.cpp utf8-utils.cpp -o $@ $(LDFLAGS)

test: $(TEST_DIR)/string-utils-test test-settings test-common-celebration test-rendering test-template-reader test-bible-reference test-colors test-request-dates
	$(TEST_DIR)/string-utils-test

.PHONY: clean depend test test-settings test-common-celebration

SETTINGS_TEST_OBJS = $(filter-out breviar.o myexpt.o,$(OBJS)) breviar-no-main.o

$(TEST_DIR)/request-date-renderer: tests/request-date-renderer.cpp myexpt.cpp Makefile $(SETTINGS_TEST_OBJS)
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -DEXPORT_TO_STRING= -I. $< myexpt.cpp $(SETTINGS_TEST_OBJS) -o $@ $(LDFLAGS)

.PHONY: test-request-dates
test-request-dates: $(TEST_DIR)/request-date-renderer
	python3 tests/request-date-test.py $(TEST_DIR)/request-date-renderer

$(TEST_DIR)/settings-xml-memory-test: tests/settings-xml-memory-test.cpp myexpt.cpp Makefile $(SETTINGS_TEST_OBJS)
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -DEXPORT_TO_STRING= -I. tests/settings-xml-memory-test.cpp myexpt.cpp $(SETTINGS_TEST_OBJS) -o $@ $(LDFLAGS)

test-settings: $(TARGET) $(TEST_DIR)/settings-xml-memory-test
	$(TEST_DIR)/settings-xml-memory-test
	python3 tests/settings-xml-test.py $(abspath $(TARGET))

test-common-celebration: $(TARGET)
	python3 tests/common-celebration-test.py $(abspath $(TARGET))

$(TEST_DIR)/prayer-renderer-test: tests/prayer-renderer-test.cpp myexpt.cpp Makefile $(SETTINGS_TEST_OBJS)
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -DEXPORT_TO_STRING= -I. tests/prayer-renderer-test.cpp myexpt.cpp $(SETTINGS_TEST_OBJS) -o $@ $(LDFLAGS)

.PHONY: test-rendering
test-rendering: $(TARGET) $(TEST_DIR)/prayer-renderer-test
	$(TEST_DIR)/prayer-renderer-test
	python3 tests/prayer-references-test.py $(abspath $(TARGET))
	python3 tests/compline-options-test.py $(abspath $(TARGET))
	python3 tests/static-text-test.py $(abspath $(TARGET))

$(TEST_DIR)/template-reader-test: tests/template-reader-test.cpp template-reader.cpp template-reader.h utf8-utils.cpp mystring.cpp
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -I. tests/template-reader-test.cpp template-reader.cpp utf8-utils.cpp mystring.cpp -o $@ $(LDFLAGS)

.PHONY: test-template-reader
test-template-reader: $(TEST_DIR)/template-reader-test
	$(TEST_DIR)/template-reader-test


$(TEST_DIR)/bible-reference-test: tests/bible-reference-test.cpp bible-reference.h $(SETTINGS_TEST_OBJS) myexpt.o
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -I. $< $(SETTINGS_TEST_OBJS) myexpt.o -o $@ $(LDFLAGS)

.PHONY: test-bible-reference
test-bible-reference: $(TEST_DIR)/bible-reference-test
	$(TEST_DIR)/bible-reference-test
	python3 tests/vatican-links-test.py $(TEST_DIR)/bible-reference-test
	python3 tests/bible-corpus-test.py $(TEST_DIR)/bible-reference-test

bible-reference.o: bible-reference.h

bible-links.o prayer-markup.o: bible-links.h bible-reference.h

-include .depend

breviar.o prayer-renderer.o prayer-markup.o: prayer-markup.h html-markup.h
html-markup.o: html-markup.h
breviar.o static-text.o prayer-markup.o: static-text.h
myhpage.o: static-text.h html-markup.h settings-text.h
breviar.o static-text.o prayer-renderer.o: prayer-renderer.h
breviar.o prayer-renderer.o prayer-markup.o: template-reader.h

breviar.o liturgia.o myhpage.o xml-settings.o appearance-colors.o: appearance-colors.h

$(TEST_DIR)/appearance-colors-test: tests/appearance-colors-test.cpp appearance-colors.cpp appearance-colors.h
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -I. tests/appearance-colors-test.cpp appearance-colors.cpp -o $@ $(LDFLAGS)

.PHONY: test-colors
test-colors: $(TARGET) $(TEST_DIR)/appearance-colors-test
	$(TEST_DIR)/appearance-colors-test
	python3 tests/appearance-colors-test.py $(abspath $(TARGET))
