-include config.mk

CXXFLAGS ?= -DMODEL_SELECTED_IN_MAKEFILE -DMODEL_linux
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

clean:
	rm -f $(TARGET) *.o .depend

.PHONY: clean depend

-include .depend
