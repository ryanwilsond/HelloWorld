TYPE=gcc
CC=g++
ifeq ($(TYPE), nogcc)
CC=./../../../../../../CodeBlocks/MinGW/bin/g++.exe
endif

all: test

.PHONY: test
test:
	$(CC) test.cpp -I../include -o test.exe
