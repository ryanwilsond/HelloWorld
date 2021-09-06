source_files = $(wildcard src/*.cpp)
object_files = $(patsubst src/%.cpp, bin/%.o, $(source_files))
assembler_files = $(wildcard asm/src/*.cpp)
assembler_object_files = $(patsubst asm/src/%.cpp, asm/bin/%.o, $(assembler_files))

ASMFLAGS=-Iasm/include -Ilib/nslib/include
# ASMLD=-Llib/nslib -lnslib
CPPFLAGS=-Iinclude
LDFLAGS=-lgdi32
CC=g++

all: $(object_files) link

.PHONY: asm
asm:
	$(CC) $(ASMFLAGS) asm/src/asm.cpp -o asm.exe
# $(CC) asm/bin/asm.o $(ASMLD) -o asm.exe

# $@ = pattern; $< = prereq; where: $@ = bin/%.o; $< = src/%.cpp
$(object_files): bin/%.o: src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

link:
	$(CC) $(object_files) $(LDFLAGS) -o main.exe

clean:
	rm -f bin/*.o
