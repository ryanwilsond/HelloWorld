source_files = $(wildcard ./src/*.cpp)
object_files = $(patsubst ./src/%.cpp, ./temp/%.o, $(source_files))

TYPE=nogcc
CPPFLAGS=-Iinclude -I./lib/nslib/include -Wall -Wextra
LDFLAGS=-Wall -Wextra
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: $(object_files) link

dirs:
	mkdir temp

.PHONY: $(object_files)
$(object_files): ./temp/%.o: ./src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

link:
	$(CC) $(object_files) $(LDFLAGS) -o bin/ccc.exe

clean:
	rm -f bin/*
	rm -f temp/*
