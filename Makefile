VERSION=debug

SOURCE_FILES = $(wildcard src/*.cpp)
OBJECT_FILES = $(patsubst src/%.cpp, bin/temp/%.o, $(SOURCE_FILES))
OUTFILE:=bin/$(VERSION)/main.exe

CPPFLAGS=-Iinclude -Wall -Wextra -Wno-unused-parameter
LDFLAGS=-lgdi32 -Wall -Wextra
CC=g++


# IGNORE: workaround for computer without g++ on path
TYPE=gcc
ifeq ($(TYPE), nogcc)
CC=./../../CodeBlocks/MinGW/bin/g++.exe
endif


all: $(OBJECT_FILES) link

dirs:
	mkdir -p bin
	mkdir -p bin/debug
	mkdir -p bin/release
	mkdir -p bin/temp

# $@ = pattern; $< = prereq; where: $@ = bin/%.o; $< = src/%.cpp
.PHONY : $(OBJECT_FILES)
$(OBJECT_FILES): bin/temp/%.o: src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

link:
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $(OUTFILE)

clean:
	rm -f bin/temp/*
	rm -f bin/debug/*
