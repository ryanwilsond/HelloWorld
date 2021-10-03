#include <stdio.h>
#include <errno.h>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"
#include "opts.h"
#include "assembler.h"
#include "compiler.h"

string self;
bool Werror;

vector<string> GetFilesContents(vector<string> filenames) {
    vector<string> contents;

    for (int i=0; i<filenames.count(); i++) {
        contents.append(file::ReadAllText(filenames[i]));
    }

    return contents;
}

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

    vector<string> g_files;
    vector<string> s_files;

    for (int i=0; i<sources.count(); i++) {
        if (sources[i].endswith('g') || sources[i].endswith("gl")) {
            g_files.append(sources[i]);
        } else {
            s_files.append(sources[i]);
        }
    }

    vector<string> gs_texts;

    string pre_text = compiler.PreProcess(g_files);

    if (ophase == 'p') {
        if (otype == 'f') {
            file::WriteAllText(outfile, pre_text);
        } else if (otype == 's') {
            print_text(pre_text);
        }

        return errno;
    }

    // segfault?
    printf("Compiling files\n");
    gs_texts = compiler.Compile(pre_text);
    printf("check 1\n");

    vector<string> s_texts = GetFilesContents(s_files);
    printf("check 2\n");

    vector<byte> bin = assembler.DoAll(g_files + s_files, gs_texts + s_texts, optimize, string(argv[0]));
    // making assembler also link for simplicity (may change later)

    printf("check 1\n");
    if (otype == 'f') {
        file::WriteAllBytes(outfile, bin);
    } else if (otype == 'a') {
        printf("{");

        if (bin.count() > 0) {
            printf(" %X", bin[0]);
        }

        for (int i=1; i<bin.count(); i++) {
            printf(", %X", bin[i]);
        }

        printf("}\n");
    }

    return 0;
}
