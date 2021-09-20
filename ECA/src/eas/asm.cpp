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
    std::map<string, string> files;

    if (f.count() != c.count()) {
        errno = 1;
        printf("Files don't match with contents\n");
        return "";
    }

    for (int i=0; i<f.count(); i++) {
        files.insert({f[i], c[i]});
    }

    string processed = "";

    for (int i=0; i<(int)f.count(); i++) {
        int linenum = 1;
        vector<string> lines;
        string filecontent = files[f[i]];

        lines = filecontent.split('\n');

        char * buf = (char *)malloc(10+strlen(f[i].c_str()));
        sprintf(buf, ". 1 \"%s\"\n", f[i].c_str());

        processed += buf;

        for (int j=0; j<lines.count(); j++, linenum++) {
            if (lines[j].startswith(".include")) {
                string tempfile = lines[j].split('"')[1];
                processed += string(". 1 \"") + tempfile + "\" 1\n";
                processed += this->resolveInclude(tempfile, path);
            } else {
                processed += lines[j] + '\n';
            }
        }
    }

    return processed;
}

vector<byte> Assembler::Dissassemble(vector<Statement> state_code) {
    vector<byte> bin;
    return bin;
}

string Assembler::resolveInclude(string filename, string path) {
}

// TODO finish watching assignment
