CCC_SOURCE_FILES = $(wildcard src/**/*.cpp)

TYPE=gcc
CFLAGS=-Iinclude -Ilibexec/nslib/include -Wall -Wextra -Wno-unused-parameter
LDFLAGS=-Wall -Wextra
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: ccc

dirs:
	mkdir temp

ccc:
	$(CC) $(CCC_SOURCE_FILES) $(CFLAGS) $(LDFLAGS) -o bin/ccc.exe

clean:
	rm -f temp/*.o
