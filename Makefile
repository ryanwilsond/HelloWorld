VERSION=debug

SOURCE_FILES:=$(wildcard src/*.cpp)
OBJECT_FILES:=$(patsubst src/%.cpp, bin/temp/%.o, $(SOURCE_FILES))
OUTFILE:=bin/$(VERSION)/main.exe

CCFLAGS=-Iinclude
CCFLAGS+=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
-Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations \
-Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual \
-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
-Wundef -Wno-unused -Werror -Wredundant-decls -Wswitch-default
LDFLAGS=-lgdi32
CC=g++

all: $(OBJECT_FILES) link

dirs:
	mkdir -p bin
	mkdir -p bin/debug
	mkdir -p bin/release
	mkdir -p bin/temp

# $@ = pattern; $< = prereq; where: $@ = bin/%.o; $< = src/%.cpp
.PHONY : $(OBJECT_FILES)
$(OBJECT_FILES): bin/temp/%.o: src/%.cpp
	$(CC) -c $(CCFLAGS) $< -o $@

link:
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $(OUTFILE)

clean:
	rm -f bin/temp/*
	rm -f bin/debug/*
