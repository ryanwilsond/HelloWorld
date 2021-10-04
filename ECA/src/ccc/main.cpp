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

vector<string> GetFilesContents(vector<string> filenames, string path) {
    vector<string> contents;

    for (int i=0; i<filenames.count(); i++) {
        if (!file::FileExists(filenames[i])) {
            string errmsg = "unknown file or directory '";
            RaiseError(errmsg + filenames[i] + "'");
        } else {
            contents.append(file::ReadAllText(filenames[i]).copy());
        }
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
    string path = "";

    Assembler assembler = Assembler();
    Compiler compiler = Compiler();

    int ccc_err = decode_arguments(argc, argv, &optimize, &otype, &ophase, &sources, &outfile, &path);

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

    string pre_text = compiler.PreProcess(g_files);

    if (ophase == 'p') {
        if (otype == 'f') {
            file::WriteAllText(outfile, pre_text);
        } else if (otype == 's') {
            print_text(pre_text);
        }

        return errno;
    }

    vector<string> gs_texts = compiler.Compile(pre_text);

    errno = 0; // using errno as local internal errors, or flag to exit program
    // might add operator=
    vector<string> s_texts = GetFilesContents(s_files, path);
    // file not found errors
    if (errno > 0) return errno;

    vector<byte> bin = assembler.DoAll(g_files + s_files, gs_texts + s_texts, optimize, string(argv[0]));
    // making assembler also link for simplicity (may change later)

    if (otype == 'f') {
        file::WriteAllBytes(outfile, bin);
    } else if (otype == 's') {
        print_text("{", false);

        if (bin.count() > 0) {
            printf(" %X", bin[0]);
        }

        for (int i=1; i<bin.count(); i++) {
            printf(", %X", bin[i]);
        }

        print_text(" }");
    }

    return 0;
}
