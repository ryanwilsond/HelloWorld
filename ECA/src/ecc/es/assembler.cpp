#include "assembler.h"

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"

int Assembler::calcInstructionSize(const Instruction& instruction, const int optimize) {
    Mnemonic ins = instruction.GetIns().value();

    

    return 0;
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

    const vector<string> lines = code.split('\n');

    // first pass
    for (int ln=0; ln<lines.count(); ln++) {
        string line = lines[ln];
        vector<string> segments = line.split();

        if (segments.count() == 0) {
            continue;
        }

        for (int i=0; i<segments.count(); i++) {
            segments[i] = segments[i].strip();
        }

        if (segments[0].startswith('.')) {
            if (segments[0] == ".start") {
                if (segments.count() > 2) {
                    RaiseError(string("invalid entry point definition: '") + line + "'");
                    RaiseCorrection(string("try: '") + segments[0] + segments[1] + "'");
                } else if (segments.count() == 1) {
                    RaiseError("invalid entry point definition: missing label or procedure name");
                }
                start = segments[1];
            }
        } else if (segments[0] == "struc") {
            if (segments.count() > 2) {
                RaiseError(string("invalid structure declaration: '") + line + "'");
                RaiseCorrection(string("try: 'struc ") + segments[1] + "'");
            } else if (segments.count() == 1) {
                RaiseError("invalid structure declaration: missing structure name");
            }
            AsmStruct struc;
            vector<string> nsegs = {""};
            int nln = ln + 1;
            while (true) {
                string nline = lines[nln];
                nsegs = nline.split(';')[0].split();
                for (int i=0; i<nsegs.count(); i++) {
                    nsegs[i] = nsegs[i].strip();
                    nsegs[i] = nsegs[i].strip('\r');
                    if (nsegs[i] == "") {
                        nsegs.pop(i);
                        i--;
                    }
                }
                if (nsegs.count() > 0) {
                    if (nsegs[0] == "ends") break;
                }
                if (nsegs.count() == 1) {
                    RaiseError(string("missing data type and value: '") + lines[nln] + "'");
                } else if (nsegs.count() == 2) {
                    RaiseError(string("missing initial value for '") + nsegs[0] + string("': '") + lines[nln] + "'");
                } else if (nsegs.count() > 3) {
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
        } else if (segments[0].endswith(":")) {
            if (segments.count() != 1) {
                RaiseError(string("invalid label declaration: '") + line + "'");
                RaiseCorrection(string("try: '") + segments[0] + "'");
            }

        } else if (segments[0] == "proc") {
        } else if (segments[0] == "endp") {
        }
    }

    // second pass
    for (int ln=0; ln<lines.count(); ln++) {
        string line = lines[ln];
    }

    statements.append(Instruction({InstructionToken(Mnemonic::NULL_INS)}));
    return statements;
}

string Assembler::PreProcess(const vector<string>& files, const vector<string>& source, const string& path) {
    assert(files.count() == source.count());
    string processed;

    for (int fn=0; fn<files.count(); fn++) {
        processed += string(". 1 \"") + files[fn] + "\"\n";

        string file_content = source[fn];
        vector<string> lines = file_content.split('\n');

        while (lines[-1] == "" || lines[-1] == "\n") {
            lines.pop();
        }

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

    while (processed[-1] == '\n') {
        processed = processed.substring(0, -2);
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
