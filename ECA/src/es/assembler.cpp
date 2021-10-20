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
        processed += string(". 1 \"") + files[fn] + "\"\n";

        string file_content = source[fn];
        vector<string> lines = file_content.split('\n');

        for (int ln=0; ln<lines.count(); ln++) {
            if (lines[ln].startswith(".include")) {
                processed += this->resolveInclude(lines[ln].substring(9), path);
                string lnnum = numToString(ln+1+1);
                processed += string(". ") + lnnum + string(" \"") + files[fn] + "\" 2\n";
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
    string absolute = filename;
    string fileLoc = "";
    string filesPath = "";

    if (file::FileExists(stdlib)) {
        fileLoc = stdlib;
    } else if (file::FileExists(absolute)) {
        fileLoc = absolute;
    } else if (file::FileExists(relative)) {
        fileLoc = relative;
    } else {
        RaiseError(string("No such file or directory '") + filename + "'");
        return result;
    }

    vector<string> splitPath = fileLoc.split('\\');
    splitPath.pop();
    string delim = "\\";
    filesPath = delim.join(splitPath);

    string fileData = file::ReadAllText(fileLoc);
    result += string(". 1 \"") + filename + string("\" 1\n");

    vector<string> filenamesTemp = {filename};
    vector<string> filesTemp = {fileData};
    Assembler copy;
    string parsedData = copy.PreProcess(filenamesTemp, filesTemp, filesPath);

    printf("parse: %s\n_", parsedData.c_str());
    vector<string> stripData = parsedData.split('\n');
    printf("%i\n", stripData.count());
    for (int i=0; i<stripData.count(); i++) {
        printf("%i:%s, ", i, stripData[i].c_str());
    }printf("\n");
    stripData.pop(0);
    printf("%i\n", stripData.count());
    for (int i=0; i<stripData.count(); i++) {
        printf("%i:%s, ", i, stripData[i].c_str());
    }printf("\n");
    string delim2 = "\n";
    printf("before join\n");
    // causes segfault
    string strippedData = delim2.join(stripData);
    printf("joined\n");
    result += strippedData;

    return result;
}
