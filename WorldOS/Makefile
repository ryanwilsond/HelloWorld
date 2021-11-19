VERSION=debug

SOURCE_FILES:=$(wildcard src/*.eas)
OUTFILE:=bin/$(VERSION)/worldos.iso

ASM=ecc
ASFLAGS=

all: disk

disk:
	$(ASM) $(SOURCE_FILES) $(ASFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin
	mkdir -p bin/temp
	mkdir -p bin/debug
	mkdir -p bin/release

clean:
	rm -f bin/temp/*
	rm -f bin/debug/*
