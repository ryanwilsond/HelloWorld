#include <stdio.h>
#include <errno.h>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "asm.h"

string self;
bool Werror = false;

void RaiseError(string m) {
    printf("%s: error: %s\n", self.c_str(), m.c_str());
    errno = 1;
}

void RaiseWarning(string m) {
    printf("%s: warning: %s\n", self.c_str(), m.c_str());
    if (Werror == true) errno = 1;
}

int main(int argc, char ** argv) {
    // convert argv to vector<string>
    vector<string> args; for (int i=1; i<argc; i++) args.append(argv[i]);

    // get executable name
    self = argv[0];
    vector<string> path = self.split('\\');
    self = path[path.count()-1];

    vector<string> infile;
    string outfile = "a.out";
    int o = 1;
    Assembler assembler = Assembler();

    // general args
    for (int i=0; i<args.count(); i++) {
        string elem = args[i];
        if (elem.startswith('-')) {
            if (elem == "-O1") o = 1; // normal
            else if (elem == "-O2") o = 2; // compact operand sizes
            else if (elem == "-Werror") Werror = true;
            else {
                if (elem != "-o") {
                    char *buf = {};
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

    // multi param args
    for (int i=0; i<args.count(); i++) {
        if (args[i] == "-o") {
            outfile = args[++i];
        }
    }

    if (infile.count() == 0) {
        RaiseError("no input files");
    }

    // arg-parse errors
    if (errno > 0) return errno;

    printf("O: %i\n", o);
    // read infile
    vector<string> texts;

    for (int i=0; i<infile.count(); i++) {
        texts.append(file::ReadAllText(infile[i]));
    }

    vector<byte> bin = assembler.Assemble(texts);
    if (errno > 0) return errno;

    // write to outfile
    file::WriteAllBytes(outfile, bin);

    return errno;
}
// add system to check filetype and accept .s and .? (custom language)
