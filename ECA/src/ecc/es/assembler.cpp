#include "assembler.h"

#include "utils.h"

int Assembler::calcInstructionSize(const Instruction& instruction, const int optimize) {
    Mnemonic ins = instruction.GetIns().value();

    int size_b = 0;

    switch (ins) {
        case HLT: {

        } break;
    }

    return size_b;
}

vector<byte> Assembler::DoAll(const vector<string>& files, const vector<string>& source, int optimize, const string& path) {
    string pre_code = this->PreProcess(files, source, path); CHECK_ERR(errno);
    vector<Statement> state_code = this->Assemble(pre_code, optimize); CHECK_ERR(errno);
    vector<byte> bin = this->Dissassemble(state_code); CHECK_ERR(errno);
    return bin;
}

vector<Statement> Assembler::Assemble(const string& code, int optimize) {
    vector<Statement> statements;
    map<string, int> labels;
    map<string, NumberToken> constants;
    map<string, PointerToken> pointers;
    map<string, AsmStruct> structs;
    string start;

    const vector<string> lines = SplitStr(code, "\n");

    // first pass
    for (int ln=0; ln<lines.size(); ln++) {
        string line = lines[ln];
        vector<string> segments = SplitStr(line);

        if (segments.size() == 0) {
            continue;
        }

        for (int i=0; i<segments.size(); i++) {
            segments[i] = StripStr(segments[i]);
        }

        if (StartswithStr(segments[0], ".") == 0) {
            if (segments[0] == ".start") {
                if (segments.size() > 2) {
                    RaiseError(string("invalid entry point definition: '") + line + "'");
                    RaiseCorrection(string("try: '") + segments[0] + segments[1] + "'");
                } else if (segments.size() == 1) {
                    RaiseError("invalid entry point definition: missing label or procedure name");
                }
                start = segments[1];
            }
        } else if (segments[0] == "struc") {
            if (segments.size() > 2) {
                RaiseError(string("invalid structure declaration: '") + line + "'");
                RaiseCorrection(string("try: 'struc ") + segments[1] + "'");
            } else if (segments.size() == 1) {
                RaiseError("invalid structure declaration: missing structure name");
            }
            AsmStruct struc;
            vector<string> nsegs = {""};
            int nln = ln + 1;
            while (true) {
                string nline = lines[nln];
                nsegs = SplitStr(SplitStr(nline, ";")[0]);
                for (int i=0; i<nsegs.size(); i++) {
                    nsegs[i] = StripStr(nsegs[i]);
                    nsegs[i] = StripStr(nsegs[i], "\r");
                    if (nsegs[i] == "") {
                        nsegs.erase(nsegs.begin() + i);
                        i--;
                    }
                }
                if (nsegs.size() > 0) {
                    if (nsegs[0] == "ends") break;
                }
                if (nsegs.size() == 1) {
                    RaiseError(string("missing data type and value: '") + lines[nln] + "'");
                } else if (nsegs.size() == 2) {
                    RaiseError(string("missing initial value for '") + nsegs[0] + string("': '") + lines[nln] + "'");
                } else if (nsegs.size() > 3) {
                    RaiseError(string("too many value for field '") + nsegs[0] + string("': '") + lines[nln] + "'");
                    RaiseCorrection(string("try: '") + nsegs[0] + string(" ") + nsegs[1] + string(" ") + nsegs[2] + "'");
                } else {
                    struc.addMember(nsegs[0], FindDataType(nsegs[1]), nsegs[2]);
                }
                nln++;
            }
            structs[segments[1]] = struc;
            ln += nln;
        } else if (segments[0] == "ends") {
            // "struc" search will skip past all ends
            RaiseError("found no structure definition to end");
        } else if (EndswithStr(segments[0], ":")) {
            if (segments.size() != 1) {
                RaiseError(string("invalid label declaration: '") + line + "'");
                RaiseCorrection(string("try: '") + segments[0] + "'");
            }

        } else if (segments[0] == "proc") {
        } else if (segments[0] == "endp") {
        }
    }

    // second pass
    for (int ln=0; ln<lines.size(); ln++) {
        string line = lines[ln];
    }

    statements.push_back(Instruction({InstructionToken(Mnemonic::NULL_INS)}));
    return statements;
}

string Assembler::PreProcess(const vector<string>& files, const vector<string>& source, const string& path) {
    assert(files.size() == source.size());
    string processed;

    for (int fn=0; fn<files.size(); fn++) {
        processed += string(". 1 \"") + files[fn] + "\"\n";

        string file_content = source[fn];
        vector<string> lines = SplitStr(file_content, "\n");

        while (lines[-1] == "" || lines[-1] == "\n") {
            lines.pop_back();
        }

        for (int ln=0; ln<lines.size(); ln++) {
            if (StartswithStr(lines[ln], ".include")) {
                processed += this->resolveInclude(lines[ln].substr(9), path);
                string lnnum = numToString(ln+1+1);
                processed += string(". ") + lnnum + string(" \"") + files[fn] + "\" 2\n";
            } else {
                processed += lines[ln] + '\n';
            }
        }
    }

    while (processed[-1] == '\n') {
        processed = processed.substr(0, processed.size()-2);
    }

    return processed + '\n';
}

vector<byte> Assembler::Dissassemble(const vector<Statement>& statements) {
    vector<byte> bin;
    return bin;
}

string Assembler::resolveInclude(const string& filename, const string& path) {
    string result;

    string stdlib = path + string(ASM_INC_PATH) + filename;
    string relative = file::GetWorkingDir() + string("\\") + filename;
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

    vector<string> splitPath = SplitStr(fileLoc, "\\");
    splitPath.pop_back();
    filesPath = JoinVec(splitPath, "\\");

    string fileData = file::ReadAllText(fileLoc);
    result += string(". 1 \"") + filename + string("\" 1\n");

    vector<string> filenamesTemp = {filename};
    vector<string> filesTemp = {fileData};
    Assembler copy;
    string parsedData = copy.PreProcess(filenamesTemp, filesTemp, filesPath);

    vector<string> stripData = SplitStr(parsedData, "\n");
    stripData.erase(stripData.begin());
    string strippedData = JoinVec(stripData, "\n");
    result += strippedData;

    while (result[-1] == '\n') {
        result = result.substr(0, result.size()-2);
    }

    return result + '\n';
}
