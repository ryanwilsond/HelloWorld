#include "asm.h"

#include <stdio.h>

#include <nsvector>
#include <nsstring>

vector<byte> Assembler::Assemble(vector<string> files, vector<string> content, int opt) {
    vector<byte> bin = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};

    for (int i=0; i<files.count(); i++) {
        printf("file: %s -> \n%s\n", files[i].c_str(), content[i].c_str());
    }

    return bin;
}
