#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "rutils.h"

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using std::vector;
using std::string;
using std::map;
using std::unordered_map;
using namespace rutils;

#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_PURPLE 13
#define COLOR_WHITE 15

#define _SYS_WOS_32 "wos32"
#define _SYS_WIN_32 "win32"
#define _SYS_WIN_64 "win64"

extern string self;
extern int warnlvl;

inline void CHECK_ERR(int ERR) { if(ERR) { exit(1); } }

/// Sets name of program when printing details to command-line
/// @param n    name
inline void SetName(char * n) {
    string rel = n;
    vector<string> path = split_str(rel, "\\");
    self = path[path.size()-1];
}

/// Prints an error
/// @param l    line number
/// @param m    message
/// @return error
inline int RaiseError(int l, string m) {
    printf("%s: ", self.c_str());
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    printf("error: ");
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    printf("%i: %s\n", l, m.c_str());
    errno = 1;
    return errno;
}

inline int RaiseError(string m) {
    printf("%s: ", self.c_str());
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    printf("error: ");
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    printf("%s\n", m.c_str());
    errno = 1;
    return errno;
}


/// Prints an error
/// @param l    line number
/// @param m    message
/// @return error
inline int RaiseWarning(int l, string m) {
    printf("%s: ", self.c_str());
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_PURPLE);
    printf("warning: ");
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    printf("%i: %s\n", l, m.c_str());
    if (warnlvl >= 2) errno = 1;
    return errno;
}

inline int RaiseWarning(string m) {
    printf("%s: ", self.c_str());
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_PURPLE);
    printf("warning: ");
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    printf("%s\n", m.c_str());
    if (warnlvl >= 2) errno = 1;
    return errno;
}

/// Prints message in green
/// @param m    message
inline void RaiseCorrection(string m) {
    string spaces;
    for (size_type i=0; i<9+self.length(); i++) spaces += " ";

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
    printf("%s\n", (spaces + m).c_str());
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
}

/// Prints text
/// @param t    text
/// @param nl   true to add newline after text
inline void print_text(string t, bool nl=true) {
    if (nl) printf("%s\n", t.c_str());
    else printf("%s", t.c_str());
}

#endif
