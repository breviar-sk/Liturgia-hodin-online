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
             mydefs.o mystring.o xml-settings.o
	g++ -o $@ $^

clean:
	rm -f $(TARGET) *.o .depend

TEST_DIR ?= .test-build

$(TEST_DIR)/string-utils-test: tests/string-utils-test.cpp mystring.cpp mystring.h utf8-utils.cpp utf8-utils.h common.h
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -I. tests/string-utils-test.cpp mystring.cpp utf8-utils.cpp -o $@ $(LDFLAGS)

test: $(TEST_DIR)/string-utils-test test-settings test-common-celebration
	$(TEST_DIR)/string-utils-test

.PHONY: clean depend test test-settings test-common-celebration

SETTINGS_TEST_OBJS = $(filter-out breviar.o myexpt.o,$(OBJS)) breviar-no-main.o

$(TEST_DIR)/settings-xml-memory-test: tests/settings-xml-memory-test.cpp myexpt.cpp Makefile $(SETTINGS_TEST_OBJS)
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) -DEXPORT_TO_STRING= -I. tests/settings-xml-memory-test.cpp myexpt.cpp $(SETTINGS_TEST_OBJS) -o $@ $(LDFLAGS)

test-settings: $(TARGET) $(TEST_DIR)/settings-xml-memory-test
	$(TEST_DIR)/settings-xml-memory-test
	python3 tests/settings-xml-test.py $(abspath $(TARGET))

test-common-celebration: $(TARGET)
	python3 tests/common-celebration-test.py $(abspath $(TARGET))

-include .depend
