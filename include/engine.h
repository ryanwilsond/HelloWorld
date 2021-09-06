#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include <stdio.h>
#include <uxtheme.h>
#include <ctime>
#include <chrono>
#include "cpu.h"
#include "ram.h"
#include "defs.h"

// Creates window with x,y dimensions and title
int InitilizeWindow(HINSTANCE hInst, HINSTANCE hPrev, int cmdShow, int winWidth, int winHeight, LPCSTR winTitle);
// Converts LPSTR to char *
char * GetArgv(LPSTR cmdLine, int * argc);
// Windows procedure callback (event handler)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
// Emulated events handler (lParam is used for unsupported mouse info)
void EventHandler(UINT Msg, int wParam, LPARAM lParam);
// Closes window
void CloseWindowM();

#endif
