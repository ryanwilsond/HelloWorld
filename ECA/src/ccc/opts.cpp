#include "opts.h"

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"

void help_prompt(string path) {
    string msg;
    string _path = path + "\\..\\help.txt";
    int ferr = file::ReadAllText(_path, &msg);
    if (ferr == 0) print_text(msg, false);
    // else printf("ferr %i\n", ferr);
}

int decode_arguments(int argc, char ** argv, int * o, char * output, char * phase, vector<string> * source, string * outfile) {
    printf("finding path\n");
    string path = argv[0];
    printf("modifying path\n");
    vector<string> split_path = path.split('\\');

    printf("finishing path\n");
    split_path.pop(split_path.count()-1);
    printf("joining path\n");
    string delim = "\\";
    path = delim.join(split_path);

    printf("found path\n");
    // general args
    argc--;
    argv++;

    int arg_err = 0;

    printf("re-finding argv\n");
    vector<string> args;
    for (int i=0; i<argc; i++) {
        args.append(argv[i]);
    }

    printf("parsing basic arguments\n");
    for (int i=0; i<args.count(); i++) {
        string elem = args[i];

        if (elem.startswith('-')) {
            if      (elem == "-O1") *o = 1; // normal (default)
            else if (elem == "-O2") *o = 2; // compact operand sizes
            else if (elem == "-E") *phase = 'p'; // stop after preprocessing
            else if (elem == "-S") *phase = 'c'; // stop after compiling
            else if (elem == "--help") { help_prompt(path); return 1; }
            else if (elem == "-Werror") Werror = true;
            else {
                if (elem != "-o") {
                    string errmsg = "unknown command line option '";
                    // errmsg += elem;
                    // errmsg += "'";
                    // RaiseError(errmsg);
                    RaiseError(errmsg + elem + "'");
                    arg_err = 1;
                }
            }

        } else if (i>0) {
            if (args[i-1] != "-o") {
                source->append(elem);
            }

        } else {
            source->append(elem);
        }
    }

    printf("defining defaults\n");
    // defaults
    if (*phase == 'a') {
        *outfile = "a.out";
    } else if (*phase == 'p') {
        *outfile = "a.i";
    } else if (*phase == 'c') {
        *outfile = "a.s";
    }

    printf("parsing complex arguments\n");
    // multi param args
    for (int i=0; i<args.count(); i++) {
        if (args[i] == "-o") {
            *outfile = args[++i];
        }
    }

    printf("checking output\n");
    if (*outfile == "@stdout") {
        *output = 's';
    }

    if (source->count() == 0) {
        RaiseError("no input files");
        arg_err = 1;
    }

    printf("returning arg_err %i\n", arg_err);
    return arg_err;
}
