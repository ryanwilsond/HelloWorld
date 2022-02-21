#include "opts.h"

#include "utils.h"

extern int warnlvl;

void help_prompt(string& path) {
    string _path = path + "\\..\\help.txt"; // bad to make it relative like this

    if (file_exists(path)) {
        string msg = read_text(_path);
        printf("%s\n", msg.c_str());
    } else {
        RaiseError("Failed to find help file: Check installation");
    }
}

int decode_arguments(
    int argc,
    char ** argv,
    int& o,
    char& output,
    char& phase,
    vector<string>& source,
    string& outfile,
    string& path,
    string& system
    ) {
    path = argv[0];
    vector<string> split_path = split_str(path, "\\");
    path = join(subset(split_path, 0, split_path.size()-2), "\\");

    // general args
    argc--;
    argv++;

    int arg_err = 0;

    vector<string> args;
    for (int i=0; i<argc; i++) {
        args.push_back(argv[i]);
    }

    // defaults
    phase = 'a';
    output = 'f';
    warnlvl = 1;

    for (size_type i=0; i<args.size(); i++) {
        string elem = args[i];

        if (startswith(elem, "-")) {
            if      (elem == "-O1") o = 1; // normal (default)
            else if (elem == "-O2") o = 2; // compact operand sizes
            else if (elem == "-E") phase = 'p'; // stop after preprocessing
            else if (elem == "-S") phase = 'c'; // stop after compiling
            else if (elem == "-win64") system = _SYS_WIN_64;
            else if (elem == "-win32") system = _SYS_WIN_32;
            else if (elem == "-wos32") system = _SYS_WOS_32;
            else if (elem == "-w") warnlvl = 0;
            else if (elem == "--help") { help_prompt(path); return 1; }
            else if (elem == "-Werror") warnlvl = 2;
            else {
                if (elem != "-o") {
                    string errmsg = "unknown command line option '";
                    RaiseError(errmsg + elem + "'");
                    arg_err = 1;
                }
            }

        } else if (i>0) {
            if (args[i-1] != "-o") {
                source.push_back(elem);
            }

        } else {
            source.push_back(elem);
        }
    }

    // defaults
    if (phase == 'a') {
        outfile = "a.out";
    } else if (phase == 'p') {
        outfile = "a.i";
    } else if (phase == 'c') {
        outfile = "a.s";
    }

    // multi param args
    for (size_type i=0; i<args.size(); i++) {
        if (args[i] == "-o") {
            outfile = args[++i];
        }
    }

    if (outfile == "@stdout") {
        output = 's';
    } else {
        output = 'f';
    }

    if (source.size() == 0) {
        RaiseError("no input files");
        arg_err = 1;
    }

    return arg_err;
}
