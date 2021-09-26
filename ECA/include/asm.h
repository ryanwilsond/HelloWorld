#ifndef ASM_H
#define ASM_H

#include <errno.h>
#include <stdio.h>

#include <initializer_list>
#include <map>

#include <nsvector>
#include <nsstring>

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;

/// Converts string to numner
/// @param literal  string literal
inline long long int stringToNum(string literal) {
    int mult = 1;
    long long int value;

    for (int i=literal.length()-1; i>=0; i++) {
        value += (literal[i]-'0')*mult;
        mult *= 10;
    }

    return value;
}

/// Converts number to literal
/// @param num  number
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

    /// Literal form of value
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

    /// Token value
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

    /// Token value
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

    /// Token value
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

    /// Gets token at index
    /// @param i    index
    Token token(int i) const {
        return this->tokens_[i];
    }

    /// Gets string representation of tokens
    string str_repr() const {
        string tmp;

        for (int i=0; i<this->tokens_.count(); i++) {
            tmp += this->tokens_[i].literal();
        }

        return tmp;
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
    /// Handles single include statement tree
    /// @param filename filename
    /// @param path     include path (relative)
    string resolveInclude(string filename, string path);

public:
    Assembler() {}

    /// Assembles files
    /// @param files    filenames
    /// @param source   code
    /// @param optimize optimize flag
    /// @param path     include path (relative)
    vector<byte> DoAll(vector<string> files, vector<string> source, int optimize, string path);

    /// Preprocessed assembly
    /// @param files    filenames
    /// @param source   code
    /// @param path     include path (relative)
    string PreProcess(vector<string> files, vector<string> source, string path);

    /// Assembles preprocessed code into statements
    /// @param code     source
    /// @param optimize optimize flag
    vector<Statement> Assemble(string code, int optimize);

    /// Dissassembles statements into bytes
    /// @param statements   statements
    vector<byte> Dissassemble(vector<Statement> statements);
};

#endif
