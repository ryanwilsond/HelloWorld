#include "eas/asm.h"

#include <stdio.h>
#include <errno.h>

#include <map>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"

vector<byte> Assembler::DoAll(vector<string> f, vector<string> c, int o, string path) {
    string pre_code = this->PreProcess(f, c, path);
    vector<Statement> state_code = this->Assemble(pre_code, o);
    vector<byte> bin = this->Dissassemble(state_code);

    return bin;
}

vector<Statement> Assembler::Assemble(string pre_code, int opt) {
    std::map<string, string> files;
    vector<Statement> state_code;

    return state_code;
}

string Assembler::PreProcess(vector<string> f, vector<string> c, string path) {
    if (f.count() != c.count()) {
        errno = 1;
        printf("Files don't match with contents\n");
        return "";
    }

    string processed = "";

    // random output, probably because of the way the string class manages memory?
    for (int fn=0; fn<f.count(); fn++) {
        processed += ". 1 ";
        processed += f[fn];
        processed += '\n';

        string file_content = c[fn];
        vector<string> lines = file_content.split('\n');

        for (int ln=0; ln<lines.count(); ln++) {
            if (lines[ln].startswith(".include")) {
                processed += "include statement\n";
            } else {
                processed += lines[ln] + '\n';
            }
            printf("%s\n", lines[ln].c_str());
        }
    }

    return processed;
}

vector<byte> Assembler::Dissassemble(vector<Statement> state_code) {
    vector<byte> bin;
    return bin;
}

string Assembler::resolveInclude(string filename, string path) {
    return filename;
}
