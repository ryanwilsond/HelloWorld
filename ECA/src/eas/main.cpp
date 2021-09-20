#include <stdio.h>
#include <errno.h>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"
#include "asm.h"

string self;
bool Werror;

int main(int argc, char ** argv) {
    // convert argv to vector<string>
    vector<string> args; for (int i=1; i<argc; i++) args.append(argv[i]);

    // get executable name
    self = argv[0];
    vector<string> path = self.split('\\');
    self = path[path.count()-1];

    vector<string> infile;
    vector<string> s_files;

    char outtype = 'f';
    char outphase = 'a';
    int o = 1;

    Assembler assembler = Assembler();

    // general args
    for (int i=0; i<args.count(); i++) {
        string elem = args[i];

        if (elem.startswith('-')) {
            if      (elem == "-O1") o = 1; // normal (default)
            else if (elem == "-O2") o = 2; // compact operand sizes
            else if (elem == "-E") outphase = 'p'; // stop after preprocessing
            else if (elem == "-D") outphase = 'c'; // stop after dissassembly
            else if (elem == "-Werror") Werror = true;
            else {
                if (elem != "-o") {
                    char * buf = (char *)malloc(strlen(elem.c_str()) + 40);
                    sprintf(buf, "Unknown command line option '%s'", elem.c_str());
                    RaiseError((string)buf);
                }
            }

        } else if (i>0) {
            if (args[i-1] != "-o") {
                infile.append(elem);
            }

        } else {
            infile.append(elem);
        }
    }


    string outfile;

    if (outphase == 'a') {
        outfile = "a.out";
    } else if (outphase == 'p') {
        outfile = "a.s";
    } else if (outphase == 'c') {
        outfile = "a.s";
    }

    // multi param args
    for (int i=0; i<args.count(); i++) {
        if (args[i] == "-o") {
            outfile = args[++i];
        }
    }

    if (outfile == "@stdout") {
        outtype = 's';
    }

    if (infile.count() == 0) {
        RaiseError("no input files");
    }

    // arg-parse errors
    if (errno > 0) return errno;

    // read infile
    vector<string> s_texts;

    for (int i=0; i<infile.count(); i++) {
        s_files.append(infile[i]);
        s_texts.append(file::ReadAllText(infile[i]));
    }

    // vector<byte> bin = assembler.Assemble(s_files, s_texts, o);

    string pre_code = assembler.PreProcess(s_files, s_texts);

    if (outphase == 'p') {
        if (outtype == 'f') {
            file::WriteAllText(outfile, pre_code);
        } else if (outtype == 's') {
            printf("%s\n", pre_code.c_str());
        }
        
        return errno;
    }

    vector<Statement> state_code = assembler.Assemble(pre_code, o);

    if (outphase == 'c') {
        string repr_code;

        for (int i=0; i<state_code.count(); i++) {
            repr_code += state_code[i].str_repr() + '\n';
        }

        if (outtype == 'f') {
            file::WriteAllText(outfile, repr_code);
        } else if (outtype == 's') {
            printf("%s\n", repr_code.c_str());
        }

        return errno;
    }

    vector<byte> bin = assembler.Dissassemble(state_code);

    // making assembler also link for simplicity (may change later)

    if (errno > 0) return errno;

    if (outtype == 'f') {
        file::WriteAllBytes(outfile, bin);
    } else if (outtype == 's') {
        printf("{ ");

        for (int i=0; i<bin.count(); i++) {
            printf("%X, ", bin[i]);
        }

        printf("}\n");
    }

    return errno;
}
