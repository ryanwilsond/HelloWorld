CCC_SOURCE_FILES = $(wildcard src/ccc/*.cpp)
EAS_SOURCE_FILES = $(wildcard src/eas/*.cpp)
EGC_SOURCE_FILES = $(wildcard src/egc/*.cpp)

TYPE=gcc
CCCFLAGS=-Iinclude -Ilibexec/nslib/include -Wall -Wextra -Wno-unused-parameter
EASFLAGS=$(CCCFLAGS) -Iinclude/eas
LDFLAGS=-Wall -Wextra
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: eas ccc

dirs:
	mkdir temp
	mkdir temp/ccc

eas:
	$(CC) $(EAS_SOURCE_FILES) $(EASFLAGS) $(LDFLAGS) -o bin/eas.exe

ccc:
	$(CC) $(CCC_SOURCE_FILES) src/eas/asm.cpp $(EGC_SOURCE_FILES) $(CCCFLAGS) $(LDFLAGS) -o bin/ccc.exe

# .PHONY: $(CCC_OBJECT_FILES)
# $(CCC_OBJECT_FILES): temp/ccc/%.o: src/ccc/%.cpp
# 	$(CC) -c $(CPPFLAGS) $< -o $@
