#include "asm.h"

#include <stdio.h>

#include <map>

#include <nsvector>
#include <nsstring>

vector<byte> Assembler::Assemble(vector<string> f, vector<string> content, int opt) {
    std::map<string, string> files;

    if (f.count() != content.count()) {
        errno = 1;
        printf("Files don't match with contents\n");
        return;
    }

    for (int i=0; i<f.count(); i++) {
        files.insert({f[i], content[i]});
    }

    string processed = this->preProcess(files);
    vector<Token> toks = this->dissassemble(processed);
    vector<byte> bin = this->toBin(toks);

    return bin;
}

string Assembler::preProcess(std::map<string, string> files) {
}

vector<Token> Assembler::dissassemble(string code) {
}

vector<byte> Assembler::toBin(vector<Token> tokens) {
}
