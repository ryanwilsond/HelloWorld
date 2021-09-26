#ifndef COMPILER_H
#define COMPILER_H

#include <nsvector>
#include <nsstring>

class Compiler {
public:
    Compiler() {}

    /// Preprocesses input files
    /// @param g_source source files
    /// @return string concatination of files
    string PreProcess(vector<string> g_source);

    /// Compiles preprocessed code
    /// @param code preprocessed code
    /// @return assembly files
    vector<string> Compile(string code);
};

#endif
