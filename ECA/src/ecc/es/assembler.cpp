#include "assembler.h"

#include "utils.h"

int Assembler::calcInstructionSize(const Instruction& instruction, const int optimize) {
    Mnemonic ins = instruction.GetIns().value();

    int size_b = 0;

    switch (ins) {
        case HLT: {
            size_b = 1;
        } break;
        case RET: {
            size_b = 1;
        } break;
        default: break;
    }

    return size_b;
}

vector<byte> Assembler::DoAll(const vector<string>& files, const vector<string>& source, int optimize, const string& path) {
    string pre_code = this->PreProcess(files, source, path); CHECK_ERR(errno);
    vector<Statement> state_code = this->Assemble(pre_code, optimize); CHECK_ERR(errno);
    vector<byte> bin = this->Disassemble(state_code); CHECK_ERR(errno);
    return bin;
}

vector<Statement> Assembler::Assemble(const string& code, int optimize) {
    vector<Statement> statements;
    map<string, int> labels;
    map<string, NumberToken> constants;
    map<string, PointerToken> pointers;
    map<string, AsmStruct> structs;
    string start;

    const vector<string> lines = split_str(code, "\n");

    // first pass
    for (size_type ln=0; ln<lines.size(); ln++) {
        string line = lines[ln];
        vector<string> segments = split_str(line);

        if (segments.size() == 0) {
            continue;
        }

        for (size_type i=0; i<segments.size(); i++) {
            segments[i] = remove_whitespace(segments[i]);
        }

        if (startswith(segments[0], ".") == 0) {
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
            size_type nln = ln + 1;

            while (true) {
                string nline = lines[nln];
                nsegs = split_str(split_str(nline, ";")[0]);
                for (size_type i=0; i<nsegs.size(); i++) {
                    nsegs[i] = remove_whitespace(nsegs[i]);
                    nsegs[i] = remove_str(nsegs[i], "\r");
                    if (nsegs[i] == "") {
                        nsegs.erase(nsegs.begin() + static_cast<long long int>(i));
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
        } else if (endswith(segments[0], ":")) {
            if (segments.size() != 1) {
                RaiseError(string("invalid label declaration: '") + line + "'");
                RaiseCorrection(string("try: '") + segments[0] + "'");
            }

        } else if (segments[0] == "proc") {
        } else if (segments[0] == "endp") {
        }
    }

    // second pass
    for (size_type ln=0; ln<lines.size(); ln++) {
        string line = lines[ln];
    }

    statements.push_back(Instruction({InstructionToken(Mnemonic::NULL_INS)}));
    return statements;
}

string Assembler::PreProcess(const vector<string>& files, const vector<string>& source, const string& path) {
    assert(files.size() == source.size());
    string processed;

    for (size_type fn=0; fn<files.size(); fn++) {
        processed += string(". 1 \"") + files[fn] + "\"\n";

        string file_content = source[fn];
        vector<string> lines = split_str(file_content, "\n");

        while (lines[lines.size()-1] == "" || lines[lines.size()-1] == "\n") {
            lines.pop_back();
        }

        for (size_type ln=0; ln<lines.size(); ln++) {
            if (startswith(lines[ln], ".include")) {
                processed += this->resolveInclude(lines[ln].substr(9), path);
                string lnnum = numToString(static_cast<long long int>(ln)+1+1);
                processed += string(". ") + lnnum + string(" \"") + files[fn] + "\" 2\n";
            } else {
                processed += lines[ln] + '\n';
            }
        }
    }

    while (processed[processed.size()-1] == '\n') {
        processed = processed.substr(0, processed.size()-2);
    }

    return processed + '\n';
}

vector<byte> Assembler::Disassemble(const vector<Statement>& statements) {
    vector<byte> bin;
    return bin;
}

string Assembler::resolveInclude(const string& filename, const string& path) {
    string result;

    string stdlib = path + string(ASM_INC_PATH) + filename;
    string relative = workingdir() + string("\\") + filename;
    string absolute = filename;
    string fileLoc;
    string filesPath;

    if (file_exists(stdlib)) {
        fileLoc = stdlib;
    } else if (file_exists(absolute)) {
        fileLoc = absolute;
    } else if (file_exists(relative)) {
        fileLoc = relative;
    } else {
        RaiseError(string("No such file or directory '") + filename + "'");
        return result;
    }

    vector<string> splitPath = split_str(fileLoc, "\\");
    splitPath.pop_back();
    filesPath = join(splitPath, "\\");

    string fileData = read_text(fileLoc);
    result += string(". 1 \"") + filename + string("\" 1\n");

    vector<string> filenamesTemp = {filename};
    vector<string> filesTemp = {fileData};
    Assembler copy;
    string parsedData = copy.PreProcess(filenamesTemp, filesTemp, filesPath);

    vector<string> stripData = split_str(parsedData, "\n");
    stripData.erase(stripData.begin());
    string strippedData = join(stripData, "\n");
    result += strippedData;

    while (result[result.size()-1] == '\n') {
        result = result.substr(0, result.size()-2);
    }

    return result + '\n';
}
