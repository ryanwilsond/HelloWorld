#ifndef COMPILER_H
#define COMPILER_H

#include "utils.h"

class Compiler {
public:
    Compiler() {}

    /// Preprocesses input files
    /// @param g_source source files
    /// @return string concatenation of files
    string PreProcess(vector<string>& g_source);

    /// Compiles preprocessed code
    /// @param code     preprocessed code
    /// @param system   what system the compile will compile for (WOS32 or WIN64)
    /// @return assembly files
    vector<string> Compile(string& code, string& system);
};

#endif
