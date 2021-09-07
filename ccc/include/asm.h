#ifndef ASM_H
#define ASM_H

#include <errno.h>
#include <stdio.h>

#include <nsvector>
#include <nsstring>

#define byte unsigned char
#define word unsigned short
#define dword unsigned int
#define qword unsigned long long

class Assembler {
public:
    Assembler() {}

    vector<byte> Assemble(vector<string>);
};

#endif
