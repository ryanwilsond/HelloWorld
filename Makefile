source_files = $(wildcard src/*.cpp)
object_files = $(patsubst src/%.cpp, temp/%.o, $(source_files))

TYPE=nogcc
CPPFLAGS=-Iinclude -Wall -Wextra
LDFLAGS=-lgdi32 -Wall -Wextra
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../gcc-temp/g++.exe
endif

all: $(object_files) link

dirs:
	mkdir temp

# $@ = pattern; $< = prereq; where: $@ = bin/%.o; $< = src/%.cpp
.PHONY : $(object_files)
$(object_files): temp/%.o: src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

link:
	$(CC) $(object_files) $(LDFLAGS) -o bin/main.exe

clean:
	rm -f bin/*
	rm -f temp/*
