#ifndef ASM_H
#define ASM_H

#include <errno.h>
#include <stdio.h>

#include <initializer_list>

#include <nsvector>
#include <nsstring>

#define byte unsigned char
#define word unsigned short
#define dword unsigned int
#define qword unsigned long long

enum TokenType {
    instruction,
    numberLiteral,
    constant,
    variable,
    label,
    structure,
    procedure,
    null,   
};

enum Mnemonic {
    hlt,
    jmp,
    lgdt,
    mov,
    ret,
};

class Token {
private:
    TokenType type_;
    string stringLiteral_;

public:
    Token() {}

    Token(string stringLiteral, TokenType type) {
    }
};

class InstructionToken : Token {
private:
    Mnemonic value_;

public:
    InstructionToken() {}

    InstructionToken(Mnemonic value) {
        this->value_ = value;
    }

    InstructionToken(string value) {
        if (value.lower() == "hlt") {
            this->value_ = Mnemonic(hlt);
        } else if (value.lower() == "jmp") {
            this->value_ = Mnemonic(jmp);
        }
    }
};

class Instruction {
private:
    vector<Token> tokens_;

public:
    Instruction(std::initializer_list<Token> tokens) {

    }
};

class Assembler {
private:
        string preProcess(vector<string>);
        string dissassemble(string);
        vector<byte> toBin(string); // finish and rename to follow conventions

public:
    Assembler() {}

    vector<byte> Assemble(vector<string>);
};

#endif
