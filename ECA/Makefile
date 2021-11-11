VERSION=debug

ECC_SOURCE_FILES = $(wildcard src/**/*.cpp)

CFLAGS=-Iinclude -Ilibexec/nslib/include -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare
LDFLAGS=
CC=g++


# IGNORE: workaround for computer without g++ on path
TYPE=gcc
ifeq ($(TYPE), nogcc)
CC=./../../../CodeBlocks/MinGW/bin/g++.exe
endif


all: ecc

dirs:
	mkdir -p bin
	mkdir -p bin/temp
	mkdir -p bin/release
	mkdir -p bin/debug

ecc:
	$(CC) $(ECC_SOURCE_FILES) $(CFLAGS) $(LDFLAGS) -o bin/$(VERSION)/ecc.exe

clean:
	rm -f bin/temp/*
	rm -f bin/debug/*
