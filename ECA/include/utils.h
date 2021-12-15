#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <stdio.h>
#include <assert.h>

#include <nsstring>
#include <nsvector>

#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_PURPLE 13
#define COLOR_WHITE 15

#define _SYS_WOS_32 "wos32"
#define _SYS_WIN_32 "win32"
#define _SYS_WIN_64 "win64"

extern string self;
extern int warnlvl;

/// Sets name of program when printing details to command-line
/// @param n    name
inline void SetName(char * n) {
    printf("setting\n");
    string rel = n;
    printf("splitting\n");
    vector<string> path = rel.split('\\');
    printf("settings self\n");
    self = path[-1];
    printf("done\n");
}

/// Prints an error
/// @param m    message
/// @return error
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
/// @param m    message
/// @return error
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
    printf("%s: ", self.c_str());
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
    printf("suggestion: ");
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    printf("%s\n", m.c_str());
}

/// Prints text
/// @param t    text
/// @param nl   true to add newline after text
inline void print_text(string t, bool nl=true) {
    if (nl) printf("%s\n", t.c_str());
    else printf("%s", t.c_str());
}

#endif
