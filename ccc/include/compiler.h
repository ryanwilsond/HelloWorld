#pragma once
#ifndef COMPILER_H
#define COMPILER_H

#include <nsvector>
#include <nsstring>

class Compiler {
public:
    Compiler() {}

    vector<string> Compile(vector<string>);
};

#endif
