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

    for (int fn=0; fn<files.count(); fn++) {
        processed += ". 1 \"";
        processed += files[fn];
        processed += "\"\n";

        string file_content = source[fn];
        vector<string> lines = file_content.split('\n');

        for (int ln=0; ln<lines.count(); ln++) {
            if (lines[ln].startswith(".include")) {
                processed += this->resolveInclude(lines[ln].substring(9), path);
            } else {
                processed += lines[ln] + '\n';
            }
        }
    }

    printf("processed:\n%s\n", processed.c_str());
    return processed;
}

vector<byte> Assembler::Dissassemble(vector<Statement> statements) {
    vector<byte> bin;
    return bin;
}

string Assembler::resolveInclude(string filename, string path) {
    string result = "";

    string stdlib = path + string("\\..\\lib\\include\\") + filename;
    string relative = file::GetWorkingDir() + string('\\') + filename;

    printf("stdlib: %s\nrelative: %s\nabsolute: %s\n", stdlib.c_str(), relative.c_str(), filename.c_str());
    // vector<string> config = file::ReadAllLines(path + )

    return result;
}
