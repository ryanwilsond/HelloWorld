#ifndef ASM_H
#define ASM_H

#include <nsvector>
#include <nsstring>
#include <nsio>

class Assembler {
private:
public:
    Assembler(){}

    vector<byte> Assemble(string);
};

vector<byte> Assembler::Assemble(string t) {
    vector<byte> bin;
    return bin;
}

#endif
