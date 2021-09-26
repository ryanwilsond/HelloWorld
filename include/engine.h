#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include <stdio.h>
#include <uxtheme.h>
#include <shellapi.h>

#include <ctime>
#include <chrono>

#include "cpu.h"
#include "ram.h"
#include "defs.h"

/// Creates window with x,y dimensions and title
/// @param hInst        handle
/// @param hPrev        ignore
/// @param cmdShow      ignore
/// @param winWidth     window width
/// @param winHeight    window height
/// @param winTitle     window display title
/// @return error
int InitilizeWindow(HINSTANCE hInst, HINSTANCE hPrev, int cmdShow, int winWidth, int winHeight, LPCSTR winTitle);

/// Converts LPSTR to char *
/// @param cmdLine  cmdline object from WinMain
/// @param argc     pointer to store argc
/// @return argv
char * GetArgv(LPSTR cmdLine, int * argc);

/// Windows procedure callback (event handler)
/// @param hwnd     window handle
/// @param msg      event
/// @param wParam   message info
/// @param lParam   message info
/// @return callback info
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/// Emulated events handler (lParam is used for unsupported mouse info)
/// @param Msg  event
/// @param wParam   int cast of wParam
/// @param lParam   message info
void EventHandler(UINT Msg, int wParam, LPARAM lParam);

/// Closes window
void CloseWindowM();

#endif
