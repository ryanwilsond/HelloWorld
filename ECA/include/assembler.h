#ifndef ASM_H
#define ASM_H

#include <initializer_list>

#include <nsvector>
#include <nsstring>
#include <nsmap>

#include "utils.h"

#define ASM_INC_PATH "\\..\\..\\lib\\wos32\\asm\\"

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;

/// Converts string to numner
/// @param literal  string literal
/// @return numeric value
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
/// @return string repr
inline string numToString(long long int num) {
    char * buf = (char*)malloc(100);
    sprintf_s(buf, 100, "%I64u", num);
    string res = buf;
    return res;
}

enum Mnemonic {
    HLT,
    RET,
    MOV,
    JMP,
    PUSH,
    POP,
    AND,
    OR,
    LGDT,
    NULL_INS,
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
    /// @return string literal
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
            this->value_ = Mnemonic(HLT);
        } else if (value.lower() == "jmp") {
            this->value_ = Mnemonic(JMP);
        } else if (value.lower() == "lgdt") {
            this->value_ = Mnemonic(LGDT);
        } else if (value.lower() == "mov") {
            this->value_ = Mnemonic(MOV);
        } else if (value.lower() == "ret") {
            this->value_ = Mnemonic(RET);
        } else {
            this->value_ = Mnemonic(NULL_INS);
        }
    }

    /// Token value
    /// @return instruction
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
    /// @return number
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
    /// @return int
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
    /// @return token at index i
    Token token(int i) const {
        return this->tokens_[i];
    }

    /// Gets string representation of tokens
    /// @return concatination of token reprs
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

class AsmStruct {
private:
    unordered_map<string, Token> members_;

public:
    AsmStruct() {}

    void addMember(string name, Token value) {
        this->members_.insert(pair<string, Token>(name, value));
    }
};

class Assembler {
private:
    /// Handles single include statement tree
    /// @param filename filename
    /// @param path     include path (relative)
    /// @return string concatination of include result (usally header file)
    string resolveInclude(const string& filename, const string& path);

public:
    Assembler() {}

    /// Assembles files
    /// @param files    filenames
    /// @param source   code
    /// @param optimize optimize flag
    /// @param path     include path (relative)
    /// @return binary data
    vector<byte> DoAll(const vector<string>& files, const vector<string>& source, int optimize, const string& path);

    /// Preprocessed assembly
    /// @param files    filenames
    /// @param source   code
    /// @param path     include path (relative)
    /// @return string concatination of files
    string PreProcess(const vector<string>& files, const vector<string>& source, const string& path);

    /// Assembles preprocessed code into statements
    /// @param code     source
    /// @param optimize optimize flag
    /// @return array of statements (code)
    vector<Statement> Assemble(const string& code, int optimize);

    /// Dissassembles statements into bytes
    /// @param statements   statements
    /// @return binary data
    vector<byte> Dissassemble(const vector<Statement>& statements);

    /// Calculates the size of an instruction (in bytes)
    /// @param instruction  statement containing instruction & operands
    /// @param optimize     optimization level (for instruction compacting)
    /// @return size in bytes of the instruction
    int calcInstructionSize(const Statement& instruction, const int optimize);
};

#endif
