#include "assembler.h"

// #include <map>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"

vector<byte> Assembler::DoAll(vector<string> files, vector<string> source, int optimize, string path) {
    string pre_code = this->PreProcess(files, source, path);
    vector<Statement> state_code = this->Assemble(pre_code, optimize);
    vector<byte> bin = this->Dissassemble(state_code);

    return bin;
}

vector<Statement> Assembler::Assemble(string code, int optimize) {
    // std::map<string, string> files;
    vector<Statement> statements;

    return statements;
}

string Assembler::PreProcess(vector<string> files, vector<string> source, string path) {
    if (files.count() != source.count()) {
        errno = 1;
        printf("Files don't match with contents\n");
        return "";
    }

    string processed = "";

    // random output, probably because of the way the string class manages memory?
    for (int fn=0; fn<files.count(); fn++) {
        processed += ". 1 ";
        processed += files[fn];
        processed += '\n';

        string file_content = source[fn];
        vector<string> lines = file_content.split('\n');

        for (int ln=0; ln<lines.count(); ln++) {
            if (lines[ln].startswith(".include")) {
                processed += "include statement\n";
            } else {
                processed += lines[ln] + '\n';
            }
        }
    }

    return processed;
}

vector<byte> Assembler::Dissassemble(vector<Statement> statements) {
    vector<byte> bin;
    return bin;
}

string Assembler::resolveInclude(string filename, string path) {
    return filename;
}
