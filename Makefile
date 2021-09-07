source_files = $(wildcard src/*.cpp)
object_files = $(patsubst src/%.cpp, temp/%.o, $(source_files))

CPPFLAGS=-Iinclude
LDFLAGS=-lgdi32
CC=g++

all: $(object_files) link

# $@ = pattern; $< = prereq; where: $@ = bin/%.o; $< = src/%.cpp
$(object_files): temp/%.o: src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

link:
	$(CC) $(object_files) $(LDFLAGS) -o bin/main.exe

clean:
	rm -f bin/*
	rm -f temp/*
