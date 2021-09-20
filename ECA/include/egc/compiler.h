#ifndef COMPILER_H
#define COMPILER_H

#include <nsvector>
#include <nsstring>

class Compiler {
public:
    Compiler() {}

    string PreProcess(vector<string>);
    vector<string> Compile(string);
};

#endif
