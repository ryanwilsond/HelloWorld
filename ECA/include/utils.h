#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <stdio.h>

#include <nsstring>
#include <nsvector>

#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_PURPLE 13
#define COLOR_WHITE 15

extern string self;
extern bool Werror;

/// Sets name of program when printing details to command-line
/// @param n    name
inline void SetName(char * n) {
    printf("assigning n to temp\n");
    string rel = string(n);
    printf("rel: %s\n", rel.c_str());
    printf("spliting path\n");
    vector<string> path = rel.split('\\');
    printf("split path\n");
    for (int i=0; i<path.count(); i++) {
        printf("%s, ", path[i].c_str());
    } printf("\n");
    printf("assigning self\n");
    self = path[path.count()-1];
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
    if (Werror == true) errno = 1;
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
