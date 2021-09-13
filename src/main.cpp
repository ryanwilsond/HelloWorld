#include <thread>
#include <fstream>
#include <iterator>
#include <vector>
#include "engine.h"
#include "cpu.h"
#include "ram.h"
#include "defs.h"

int ramSize = 2560 + (768000); // 5 sectors + video ram

int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;
int WIN_RES_RATIO = 2;
int RES_X = 640;
int RES_Y = 400;
int BORDER_X = (WINDOW_WIDTH - (RES_X*WIN_RES_RATIO)) / 2;
int BORDER_Y = (WINDOW_HEIGHT - (RES_Y*WIN_RES_RATIO)) / 2;
int FPS = 30;

char KEYBOARD_SIGNATURE = 0b0001;
word KEYBOARD_PORT = 1;
char EVENT_KEYDOWN = 0b0001;
char EVENT_KEYUP = 0b0010;

LPCSTR winTitle = (LPCSTR)L"Put some fake brand name here or something";
RAM ram;
CPU cpu;

void StartCPUThread() {
    cpu.Start(&ram);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdLine, int cmdShow) { int argc; char * argv = GetArgv(cmdLine, &argc);
    if (InitilizeWindow(hInst, hPrev, cmdShow, WINDOW_WIDTH, WINDOW_HEIGHT, winTitle)) return errno;
    ram.Init(ramSize);

    std::ifstream infile("disk.bin", std::ios_base::binary);

    std::vector<unsigned char> diskbytes(
        (std::istreambuf_iterator<char>(infile)),
        (std::istreambuf_iterator<char>())
    );

    infile.close();

    while ((int)diskbytes.size() < ramSize) diskbytes.push_back(0);

    for (int i=0; i<ramSize; i++) {
        ram.memory[i] = diskbytes[i];
    }

    cpu.OFF = false; // prevent race condition with exit condition in msg loop
    std::thread cpuThread(StartCPUThread);

    MSG Msg;
    // Needs to be on main thread
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
        if (cpu.OFF == true) CloseWindowM();
        // RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);
    }

    cpu.Exit();
    cpuThread.join();
    ram.Destroy();

    return Msg.wParam; // implicit int conversion
}
