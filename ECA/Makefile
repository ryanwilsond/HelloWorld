ECC_SOURCE_FILES = $(wildcard src/**/*.cpp)

TYPE=gcc
CFLAGS=-Iinclude -Ilibexec/nslib/include -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare
LDFLAGS=
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: ecc

dirs:
	mkdir temp

ecc:
	$(CC) $(ECC_SOURCE_FILES) $(CFLAGS) $(LDFLAGS) -o bin/ecc.exe

clean:
	rm -f temp/*.o
