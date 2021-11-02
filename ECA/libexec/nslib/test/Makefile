TYPE=gcc
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../../../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: test heap

.PHONY: test
test:
	$(CC) test.cpp -I../include -o test.exe

.PHONY: heap
heap:
	$(CC) heap.cpp -I../include -o heap.exe
