#include "asm.h"

#include <stdio.h>

#include <map>

#include <nsvector>
#include <nsstring>
#include <nsio>

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
    printf("%s\n", processed.c_str());
    vector<Statement> statements = this->dissassemble(processed);
    bin = this->toBin(statements);

    return bin;
}

string Assembler::preProcess(vector<string> filenames, std::map<string, string> files) {
    string processed = "";

    for (int i=0; i<(int)filenames.count(); i++) {
        int linenum = 1;
        vector<string> lines;
        string filecontent = files[filenames[i]];

        lines = filecontent.split('\n');

        char * buf = (char *)malloc(10+strlen(filenames[i].c_str()));
        sprintf(buf, ". 1 \"%s\"", filenames[i].c_str());

        processed += buf;

        for (int j=0; j<lines.count(); j++, linenum++) {
            if (lines[j].startswith(".include")) {
                string tempfile = lines[j].split('"')[1];
                processed += string(". 1 \"") + tempfile + "\" 5\n";
            } else {
                processed += lines[j] + '\n';
            }
        }
    }

    return processed;
}

vector<Statement> Assembler::dissassemble(string code) {
    vector<Statement> toks;
    return toks;
}

vector<byte> Assembler::toBin(vector<Statement> tokens) {
    vector<byte> bin;
    return bin;
}
