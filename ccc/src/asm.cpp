#include "asm.h"

#include <stdio.h>

#include <nsvector>
#include <nsstring>

vector<byte> Assembler::Assemble(vector<string> ts) {
    vector<byte> bin = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    printf("files: %i\n", ts.count());
    return bin;
}
