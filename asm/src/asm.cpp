#include "asm.h"
#include <stdio.h>

string Error = "Error";
string Warning = "Warning";
string InvalidDeclaration = ":InvalidDeclaration";
string Unknown = ":Unknown";
string PreprocessStatement = ":PreprocessStatement";
string Constant = ":Constant";
string BadCommandLine = ":BadCommandLine";
string InvalidOption = ":InvalidOption";
string NotPresent = ":NotPresent";


string self;

void RaiseError(string e, string m) {
    printf("%s: %s: %s\n", self, Error + e, m);
}

int main(int argc, char ** argv) {
    // convert argv to vector<string>
    vector<string> args;
    for (int i=1; i<argc; i++) args.append(argv[i]);

    // get executable name
    self = argv[0];
    vector<string> path = self.split('\\');
    self = path[path.count-1];

    string infile = "";
    string outfile = "";
    string text;
    int o = 1;
    bool error = false;
    Assembler assembler;
    vector<byte> bin;

    // general args
    for (int i=0; i<args.count; i++) {
        string elem = args[i];
        if (elem.startswith('-')) {
            if (elem == "-O1") o = 1; // normal
            else if (elem == "-O2") o = 2; // compact operand sizes
            else {
                if (elem != "-o") {
                    char * buf;
                    sprintf(buf, "Unknown command line option '%s'", elem);
                    RaiseError(BadCommandLine + InvalidOption, string(buf));
                    error = true;
                }
            }
        }
    }

    // multi param args
    for (int i=0; i<args.count; i++) {
        if (args[i] == "-o") {
            outfile = args[++i];
        } else if (!args[i].startswith('-')) {
            infile = args[i];
        }
    }

    if (infile == "") {
        RaiseError(BadCommandLine + NotPresent, "no input files");
        error = 1;
    }

    // infile
    if (outfile == "") {
        outfile = infile.split('.')[0] + ".bin";
    }

    // arg-parse errors
    if (error) return 1;

    // read infile
    text = file::ReadAllText(infile);
    printf("%s\n", text);
    return 0;

    // assemble
    bin = assembler.Assemble(text);
    if (bin.count == 0) return 1;

    // write to outfile
    file::WriteAllBytes(outfile, bin);

    return 0;
}
