CC=g++
CCFLAGS=-I../include
# CCFLAGS+=-Wall -Wextra

all: nsvector nsstring nsmap nsio nslist nsheap

test:
	$(CC) $(CCFLAGS) test.cpp -o test.exe

.PHONY: nsvector
nsvector:
	$(CC) $(CCFLAGS) src/nsvector_test.cpp -o nsvector_test.exe

.PHONY: nsstring
nsstring:
	$(CC) $(CCFLAGS) src/nsstring_test.cpp -o nsstring_test.exe

.PHONY: nsio
nsio:
	$(CC) $(CCFLAGS) src/nsio_test.cpp -o nsio_test.exe

.PHONY: nsmap
nsmap:
	$(CC) $(CCFLAGS) src/nsmap_test.cpp -o nsmap_test.exe

.PHONY: nslist
nslist:
	$(CC) $(CCFLAGS) src/nslist_test.cpp -o nslist_test.exe

.PHONY: nsheap
nsheap:
	$(CC) $(CCFLAGS) src/nsheap_test.cpp -o nsheap_test.exe
