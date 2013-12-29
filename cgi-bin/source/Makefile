-include config.mk

CXXFLAGS ?= -DMODEL_SELECTED_IN_MAKEFILE -DMODEL_linux_citania
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

print_codes: print_codes.o breviar-no-main.o citania.o dbzaltar.o liturgia.o \
             mygetopt.o mylog.o myhpage.o myexpt.o cgiutils.o myconf.o \
             mydefs.o mystring.o 
	g++ -o $@ $^

clean:
	rm -f $(TARGET) *.o .depend

.PHONY: clean depend

-include .depend
