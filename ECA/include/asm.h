#ifndef ASM_H
#define ASM_H

#include <errno.h>
#include <stdio.h>

#include <initializer_list>
#include <map>

#include <nsvector>
#include <nsstring>

#define byte unsigned char
#define word unsigned short
#define dword unsigned int
#define qword unsigned long long

inline long long int stringToNum(string literal) {
    int mult = 1;
    long long int value;

    for (int i=literal.length()-1; i>=0; i++) {
        value += (literal[i]-'0')*mult;
        mult *= 10;
    }

    return value;
}

inline string numToString(long long int num) {
    char * buf = {};
    sprintf(buf, "%I64u", num);
    return (string)buf;
}

enum Mnemonic {
    hlt,
    jmp,
    lgdt,
    mov,
    ret,
    null_ins,
};

class Token {
private:
    string stringLiteral_;

public:
    Token() {}

    Token(string stringLiteral) {
        this->stringLiteral_ = stringLiteral;
    }

    string literal() const {
        return this->stringLiteral_;
    }
};

class InstructionToken : public Token {
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
        } else if (value.lower() == "lgdt") {
            this->value_ = Mnemonic(lgdt);
        } else if (value.lower() == "mov") {
            this->value_ = Mnemonic(mov);
        } else if (value.lower() == "ret") {
            this->value_ = Mnemonic(ret);
        } else {
            this->value_ = Mnemonic(null_ins);
        }
    }

    Mnemonic value() const {
        return this->value_;
    }
};

class NumberToken : public Token {
private:
    long long int value_;
    string stringLiteral_;

public:
    NumberToken() {}

    NumberToken(string stringLiteral) {
        this->stringLiteral_ = stringLiteral;
        this->value_ = stringToNum(stringLiteral);
    }

    NumberToken(long long int value) {
        this->value_ = value;
        this->stringLiteral_ = numToString(value);
    }

    long long int value() const {
        return this->value_;
    }
};

class PointerToken : public Token {
private:
    int value_;
    string stringLiteral_;

public:
    PointerToken() {}

    PointerToken(string stringLiteral) {
        this->stringLiteral_ = stringLiteral;
        this->value_ = (int)stringToNum(stringLiteral);
    }

    PointerToken(int value) {
        this->value_ = value;
        this->stringLiteral_ = numToString((long long int)value);
    }

    int value() const {
        return this->value_;
    }
};

class Statement {
private:
    vector<Token> tokens_;

public:
    Statement() {}

    Statement(std::initializer_list<Token> tokens) {
        this->tokens_ = tokens;
    }

    Token token(int n) const {
        return this->tokens_[n];
    }

    Token operator[](int n) const {
        return this->token(n);
    }
};

class Instruction : public Statement {
private:
    vector<Token> tokens_;

public:
    Instruction() {}

    Instruction(std::initializer_list<Token> tokens) {
        this->tokens_ = tokens;
    }
};

class PreprocessDirective : public Statement {
private:
    vector<Token> tokens_;

public:
    PreprocessDirective() {}

    PreprocessDirective(std::initializer_list<Token> tokens) {
        this->tokens_ = tokens;
    }
};

class Assembler {
private:
        string preProcess(vector<string>, std::map<string, string>);
        vector<Statement> dissassemble(string);
        vector<byte> toBin(vector<Statement>);

public:
    Assembler() {}

    vector<byte> Assemble(vector<string>, vector<string>, int);
};

#endif
