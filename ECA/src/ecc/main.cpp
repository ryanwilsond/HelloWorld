#include <stdio.h>
#include <errno.h>

#include <nsvector>
#include <nsstring>
#include <nsio>

#include "utils.h"
#include "opts.h"
#include "assembler.h"
#include "compiler.h"

// need to look more into inline vs macro
// doing inline here just because intellisense is not a fan of macros
inline void CHECK_ERR(int ERR) { if(ERR) exit(1); }
// #define CHECK_ERR(ERR) ({ if(ERR){ exit(1); } })

string self;
int warnlvl;

static vector<string> GetFilesContents(vector<string> filenames, string path) {
    vector<string> contents;

    for (int i=0; i<filenames.count(); i++) {
        if (!file::FileExists(filenames[i])) {
            string errmsg = "unknown file or directory '";
            RaiseError(errmsg + filenames[i] + "'");
        } else {
            contents.append(file::ReadAllText(filenames[i]));
        }
    }

    return contents;
}

int main(int argc, char ** argv) {
    printf("testing\n");
    SetName(argv[0]);
    printf("testing\n");

    vector<string> sources;
    string outfile;
    string system = _SYS_WOS_32;

    char otype;
    char ophase;
    int optimize = 1; // default optimization
    string path;

    Assembler assembler = Assembler();
    Compiler compiler = Compiler();

    int ccc_err = decode_arguments(argc, argv, &optimize, &otype, &ophase, &sources, &outfile, &path, &system, &warnlvl);

    CHECK_ERR(ccc_err);

    vector<string> g_files;
    vector<string> s_files;

    printf("assigning\n");
    for (int i=0; i<sources.count(); i++) {
        if (sources[i].endswith('g') || sources[i].endswith("gl")) {
            g_files.append(sources[i]);
        } else {
            s_files.append(sources[i]);
        }
    }

    printf("compiling\n");
    string pre_text = compiler.PreProcess(g_files);

    if (ophase == 'p') {
        if (otype == 'f') {
            file::WriteAllText(outfile, pre_text);
        } else if (otype == 's') {
            print_text(pre_text);
        }

        return errno;
    }

    errno = 0;
    vector<string> gs_texts = compiler.Compile(pre_text, system);
    CHECK_ERR(errno);

    if (ophase == 'c') {
        if (otype == 'f') {
            file::WriteAllText(outfile, pre_text);
        } else if (otype == 's') {
            print_text(pre_text);
        }

        return errno;
    } else {
        if (system == _SYS_WIN_64) {
            RaiseError("Currently cant assemble for win32 (suggested alternative: GCC as)");
            return 1;
        }
    }

    printf("getting content\n");
    vector<byte> bin;
    errno = 0;
    vector<string> s_texts = GetFilesContents(s_files, path);
    CHECK_ERR(errno);

    // making assembler also link for simplicity (may change later)
    if (system == _SYS_WOS_32) {
        errno = 0;
        printf("assembling\n");
        bin = assembler.DoAll(g_files + s_files, gs_texts + s_texts, optimize, path);
        CHECK_ERR(errno);
    }

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
