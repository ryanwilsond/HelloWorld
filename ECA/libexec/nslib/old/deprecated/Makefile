source_files = $(wildcard ./src/*.cpp)
object_files = $(patsubst ./src/%.cpp, ./bin/%.o, $(source_files))

CPPFLAGS=-Iinclude
CC=g++
AR=ar

all: dep libnslib.a

dep:
	$(CC) $(CPPFLAGS) -c src/nsvector.cpp -o bin/nsvector.o
	$(CC) $(CPPFLAGS) -c src/nsstring.cpp -o bin/nsstring.o
	$(CC) $(CPPFLAGS) -c src/nsio.cpp -o bin/nsio.o

.PHONY : libnslib.a
libnslib.a: $(object_files)
	$(AR) rcu $@ $(object_files)
