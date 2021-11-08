#include "assembler.h"

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"

#define ASM_INC_PATH "\\..\\lib\\wos32\\asm\\"

int Assembler::calcInstructionSize(Statement instruction) {
    return 0;
}

vector<byte> Assembler::DoAll(vector<string> files, vector<string> source, int optimize, string path) {
    printf("preprocessing\n");
    string pre_code = this->PreProcess(files, source, path);
    printf("assembling\n");
    vector<Statement> state_code = this->Assemble(pre_code, optimize);
    printf("dissassembling\n");
    vector<byte> bin = this->Dissassemble(state_code);

    return bin;
}

vector<Statement> Assembler::Assemble(string code, int optimize) {
    vector<Statement> statements;
    map<string, int> labels;
    map<string, NumberToken> constants; // constants cant be arrays
    map<string, PointerToken> pointers;
    map<string, AsmStruct> structs;

    const vector<string> lines = code.split('\n');

    // first pass
    for (int ln=0; ln<lines.count(); ln++) {
        string line = lines[ln];
        // strip tab/spaces here (maybe add string::strip method)

        if (line.startswith('.')) {

        } else if (line.startswith("struc")) {

        } else if (line.startswith("ends")) {

        } else if (line.endswith(":")) {

        }
    }

    // second pass
    for (int ln=0; ln<lines.count(); ln++) {
        string line = lines[ln];
    }

    return statements;
}

string Assembler::PreProcess(vector<string> files, vector<string> source, string path) {
    printf("asserting\n");
    assert(files.count() == source.count());

    string processed;

    printf("loop\n");
    for (int fn=0; fn<files.count(); fn++) {
        processed += string(". 1 \"") + files[fn] + "\"\n";

        string file_content = source[fn];
        vector<string> lines = file_content.split('\n');

        while (lines[-1] == "" || lines[-1] == "\n") {
            lines.pop();
        }
        printf("cleaned lines\n");

        for (int ln=0; ln<lines.count(); ln++) {
            if (lines[ln].startswith(".include")) {
                printf("res include\n");
                processed += this->resolveInclude(lines[ln].substring(9), path);
                string lnnum = numToString(ln+1+1);
                processed += string(". ") + lnnum + string(" \"") + files[fn] + "\" 2\n";
            } else {
                processed += lines[ln] + '\n';
            }
        printf("  processed: %s\n", processed.c_str());
        }
    }

    while (processed[-1] == '\n') {
        processed = processed.substring(0, -2);
    }

    return processed + '\n';
}

vector<byte> Assembler::Dissassemble(vector<Statement> statements) {
    vector<byte> bin;
    return bin;
}

string Assembler::resolveInclude(string filename, string path) {
    string result;

    string stdlib = path + string(ASM_INC_PATH) + filename;
    string relative = file::GetWorkingDir() + string('\\') + filename;
    string absolute = filename;
    string fileLoc;
    string filesPath;

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
    filesPath = string::join("\\", splitPath);

    string fileData = file::ReadAllText(fileLoc);
    result += string(". 1 \"") + filename + string("\" 1\n");

    vector<string> filenamesTemp = {filename};
    vector<string> filesTemp = {fileData};
    Assembler copy;
    string parsedData = copy.PreProcess(filenamesTemp, filesTemp, filesPath);

    vector<string> stripData = parsedData.split('\n');
    stripData.pop(0);
    string strippedData = string::join("\n", stripData);
    result += strippedData;

    while (result[-1] == '\n') {
        result = result.substring(0, -2);
    }

    return result + '\n';
}
