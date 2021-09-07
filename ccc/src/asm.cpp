#include "asm.h"

#include <stdio.h>

#include <nsvector>
#include <nsstring>

vector<byte> Assembler::Assemble(vector<string> ts) {
    vector<byte> bin;

    for (int i=0; i<ts.count(); i++) {
        printf("%s\n", ts[i]);
    }

    errno = 1;
    return bin;
}
