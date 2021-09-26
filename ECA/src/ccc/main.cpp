#include <stdio.h>
#include <errno.h>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"
#include "opts.h"
#include "asm.h"
#include "compiler.h"

string self;
bool Werror;

int main(int argc, char ** argv) {
    SetName(argv[0]);

    vector<string> sources;
    string outfile = "";

    char otype = 'f';
    char ophase = 'a';
    int optimize = 1;

    Assembler assembler = Assembler();
    Compiler compiler = Compiler();

    int ccc_err = decode_arguments(argc, argv, &optimize, &otype, &ophase, &sources, &outfile);

    if (ccc_err > 0) return 0;
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
