#include <stdio.h>
#include <errno.h>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"
#include "opts.h"
#include "asm.h"
#include "compiler.h"

int main(int argc, char ** argv) {
    SetName(string(argv[0]));

    vector<string> infile;
    vector<string> s_files;
    vector<string> g_files;

    char outtype = 'f';
    char outphase = 'a';
    int o = 1;

    Assembler assembler = Assembler();
    Compiler compiler = Compiler();

    int ccc_err = decode_arguments(argc, argv);
    // general args
    // for (int i=0; i<args.count(); i++) {
    //     string elem = args[i];

    //     if (elem.startswith('-')) {
    //         if      (elem == "-O1") o = 1; // normal (default)
    //         else if (elem == "-O2") o = 2; // compact operand sizes
    //         else if (elem == "-E") outphase = 'p'; // stop after preprocessing
    //         else if (elem == "-S") outphase = 'c'; // stop after compiling
    //         else if (elem == "-Werror") Werror = true;
    //         else {
    //             if (elem != "-o") {
    //                 char * buf = (char *)malloc(strlen(elem.c_str()) + 40);
    //                 sprintf(buf, "unknown command line option '%s'", elem.c_str());
    //                 RaiseError((string)buf);
    //             }
    //         }

    //     } else if (i>0) {
    //         if (args[i-1] != "-o") {
    //             infile.append(elem);
    //         }

    //     } else {
    //         infile.append(elem);
    //     }
    // }

    // string outfile;

    // if (outphase == 'a') {
    //     outfile = "a.out";
    // } else if (outphase == 'p') {
    //     outfile = "a.i";
    // } else if (outphase == 'c') {
    //     outfile = "a.s";
    // }

    // // multi param args
    // for (int i=0; i<args.count(); i++) {
    //     if (args[i] == "-o") {
    //         outfile = args[++i];
    //     }
    // }

    // if (outfile == "@stdout") {
    //     outtype = 's';
    // }

    // if (infile.count() == 0) {
    //     RaiseError("no input files");
    // }

    // // arg-parse errors
    // if (errno == 1) return errno;

    // // read infile
    // vector<string> s_texts;

    // for (int i=0; i<infile.count(); i++) {
    //     if (infile[i].endswith('g')) {
    //         g_files.append(infile[i]);
    //     } else {
    //         s_files.append(infile[i]);
    //         s_texts.append(file::ReadAllText(infile[i]));
    //     }
    // }

    // vector<string> gs_texts;

    // string pre_text = compiler.PreProcess(g_files);

    // if (outphase == 'p') {
    //     if (outtype == 'f') {
    //         file::WriteAllText(outfile, pre_text);
    //     } else if (outtype == 's') {
    //         printf("%s\n", pre_text.c_str());
    //     }

    //     return errno;
    // }

    // gs_texts = compiler.Compile(pre_text);

    // vector<byte> bin = assembler.DoAll(g_files + s_files, gs_texts + s_texts, o, string(argv[0]));
    // // making assembler also link for simplicity (may change later)

    // if (outtype == 'f') {
    //     file::WriteAllBytes(outfile, bin);
    // } else if (outtype == 's') {
    //     printf("{ ");

    //     for (int i=0; i<bin.count(); i++) {
    //         printf("%X, ", bin[i]);
    //     }

    //     printf("}\n");
    // }

    return 0;
}
