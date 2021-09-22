#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <errno.h>

#include <nsstring>

#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_PURPLE 13
#define COLOR_WHITE 15

extern string self;
extern bool Werror;

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

inline void RaiseCorrection(string m) {
    printf("%s: ", self.c_str());
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
    printf("suggestion: ");
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    printf("%s\n", m.c_str());
}

#endif
