source_files = $(wildcard ./src/*.cpp)
object_files = $(patsubst ./src/%.cpp, ./bin/%.o, $(source_files))

CPPFLAGS=-Iinclude -I./../lib/nslib/include
LDFLAGS=
CC=g++

all: $(object_files)

.PHONY: $(object_files)
$(object_files): ./bin/%.o: ./src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@
