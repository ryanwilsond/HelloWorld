TYPE=gcc
CC=g++
CCFLAGS=-I../include
# CCFLAGS=-Wall -Wextra
ifeq ($(TYPE), nogcc)
CC=./../../../../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: nsvector nsstring nsmap nsio nslist nsheap

.PHONY: nsvector
nsvector:
	$(CC) $(CCFLAGS) nsvector_test.cpp -o nsvector_test.exe

.PHONY: nsstring
nsstring:
	$(CC) $(CCFLAGS) nsstring_test.cpp -o nsstring_test.exe

.PHONY: nsio
nsio:
	$(CC) $(CCFLAGS) nsio_test.cpp -o nsio_test.exe

.PHONY: nsmap
nsmap:
	$(CC) $(CCFLAGS) nsmap_test.cpp -o nsmap_test.exe

.PHONY: nslist
nslist:
	$(CC) $(CCFLAGS) nslist_test.cpp -o nslist_test.exe

.PHONY: nsheap
nsheap:
	$(CC) $(CCFLAGS) nsheap_test.cpp -o nsheap_test.exe
