CCC_SOURCE_FILES = $(wildcard src/ccc/*.cpp)
CCC_OBJECT_FILES = $(patsubst src/ccc/%.cpp, temp/ccc/%.o, $(source_files))

TYPE=gcc
CPPFLAGS=-Iinclude -Ilibexec/nslib/include -Wall -Wextra -Wno-unused-parameter
LDFLAGS=-Wall -Wextra
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: ccc

dirs:
	mkdir temp
	mkdir temp/ccc

ccc:
	$(CC) $(CCC_SOURCE_FILES) $(CPPFLAGS) $(LDFLAGS) -o bin/ccc.exe

# .PHONY: $(CCC_OBJECT_FILES)
# $(CCC_OBJECT_FILES): temp/ccc/%.o: src/ccc/%.cpp
# 	$(CC) -c $(CPPFLAGS) $< -o $@
