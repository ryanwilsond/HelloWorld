#include "asm.h"

#include <stdio.h>

#include <map>

#include <nsvector>
#include <nsstring>

vector<byte> Assembler::Assemble(vector<string> f, vector<string> content, int opt) {
    std::map<string, string> files;
    vector<byte> bin;

    if (f.count() != content.count()) {
        errno = 1;
        printf("Files don't match with contents\n");
        return bin;
    }

    for (int i=0; i<f.count(); i++) {
        files.insert({f[i], content[i]});
    }

    string processed = this->preProcess(f, files);
    vector<Token> toks = this->dissassemble(processed);
    bin = this->toBin(toks);

    return bin;
}

string Assembler::preProcess(vector<string> filenames, std::map<string, string> files) {
    string processed;

    for (int i=0; i<(int)files.size(); i++) {
        vector<string> lines;
        string val = files[filenames[i]];
        lines = val.split('\n');

        for (int j=0; j<lines.count(); j++) {
            // look for .start (entry point)
        }
    }

    return processed;
}

vector<Token> Assembler::dissassemble(string code) {
    vector<Token> toks;
    return toks;
}

vector<byte> Assembler::toBin(vector<Token> tokens) {
    vector<byte> bin;
    return bin;
}
