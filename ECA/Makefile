VERSION=debug

ECC_SOURCE_FILES:=$(wildcard src/ecc/**/*.cpp) $(wildcard src/ecc/*.cpp)

CCFLAGS=-Iinclude -Ilibexec/rutils/include
# CCFLAGS+=-Ilibexec/nslib/include
CCFLAGS+=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
-Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations \
-Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual \
-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
-Wundef -Wno-unused -Werror -Wredundant-decls -Wswitch-default
LDFLAGS=
CC=g++

all: ecc

dirs:
	mkdir -p bin
	mkdir -p bin/temp
	mkdir -p bin/release
	mkdir -p bin/debug

ecc:
	$(CC) $(ECC_SOURCE_FILES) $(CCFLAGS) $(LDFLAGS) -o bin/$(VERSION)/ecc.exe

clean:
	rm -f bin/temp/*
	rm -f bin/debug/*
