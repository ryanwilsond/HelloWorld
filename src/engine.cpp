#include "engine.h"

extern CPU cpu;
extern RAM ram;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int WIN_RES_RATIO;
extern int RES_X;
extern int RES_Y;
extern int BORDER_X;
extern int BORDER_Y;
extern int FPS;
extern char KEYBOARD_SIGNATURE;
extern word KEYBOARD_PORT;
extern char EVENT_KEYDOWN;
extern char EVENT_KEYUP;

auto timer = std::chrono::system_clock::now();
auto now = std::chrono::system_clock::now();

char * GetArgv(LPSTR cmdLine, int * argc) {
    return (char *)CommandLineToArgvW((LPCWSTR)cmdLine, argc);
}

void EventHandler(UINT Msg, int wParam, LPARAM lParam) {
    word interruptData;
    word kbSigWord = (KEYBOARD_SIGNATURE & 0b1111) << 12;
    word eventKeydownWord = (EVENT_KEYDOWN & 0b1111) << 8;
    word eventKeyupWord = (EVENT_KEYUP & 0b1111) << 8;

    switch (Msg) {
        case WM_KEYDOWN:
            interruptData = kbSigWord | eventKeydownWord | (char)wParam;
            break;
        case WM_KEYUP:
            interruptData = kbSigWord | eventKeyupWord | (char)wParam;
            break;
        default:
            return;
    }

    cpu.ports[KEYBOARD_PORT] = interruptData;
    cpu.InterruptRequest(32);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    now = std::chrono::system_clock::now();
    auto elapsed = now-timer;
    int ielap = (int)elapsed.count();

    if (ielap > (1/FPS)) {
        timer = now;
        EventHandler(msg, (int)wParam, lParam);
    }

    PAINTSTRUCT ps;
    HDC hdc;
    HDC hdesktop = GetDC(0);
    RECT rect;
    HDC memdc = CreateCompatibleDC(hdesktop);
    HBITMAP hbitmap = CreateCompatibleBitmap(hdesktop, WINDOW_WIDTH, WINDOW_HEIGHT);
    HBITMAP oldmap = (HBITMAP)SelectObject(memdc, hbitmap);

    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            // Moving this to another function is useless as it is only used here in the same file
            if (timer == now) {
                for (int i=0; i<RES_X; i++) {
                    for (int j=0; j<RES_Y; j++) {
                        rect.left = BORDER_X + i * WIN_RES_RATIO;
                        rect.top = BORDER_Y + j * WIN_RES_RATIO;
                        rect.right = BORDER_X + (i+1) * WIN_RES_RATIO;
                        rect.bottom = BORDER_Y + (j+1) * WIN_RES_RATIO;
                        SetDCBrushColor(memdc, RGB(255, 0, 0)); // temp color for testing
                        FillRect(memdc, &rect, (HBRUSH)GetStockObject(DC_BRUSH));
                    }
                }
            }

            BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, memdc, 0, 0, SRCCOPY);

            SelectObject(memdc, oldmap);
            DeleteDC(memdc);
            DeleteObject(hbitmap);
            EndPaint(hwnd, &ps);
            break;
        case WM_ERASEBKGND:
            return 1;
        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    return 0;
}

void CloseWindowM() {
    PostQuitMessage(0);
}

int InitilizeWindow(HINSTANCE hInst, HINSTANCE hPrev, int cmdShow, int winWidth, int winHeight, LPCSTR winTitle) {
    WNDCLASSEX wc;

    // Window Properties
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = (LPCSTR)L"winClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        printf("Window registration failed\n");
        errno = ERROR_PKINIT_FAILURE;
        return 1;
    }

    DWORD style1 = WS_EX_APPWINDOW;
    DWORD style2 = WS_POPUP;
    auto self = (LPVOID)NULL; // pass this for class

    // Create Window
    HWND hWnd = CreateWindowExA(
        style1,
        (LPCSTR)L"winClass",
        winTitle,
        style2,
        CW_USEDEFAULT, CW_USEDEFAULT,
        winWidth, winHeight,
        NULL, NULL, hInst, self);

    if (hWnd == NULL) {
        printf("Window creation failed\n");
        errno = ERROR_PKINIT_FAILURE;
        return 1;
    }

    ShowWindow(hWnd, cmdShow);
    UpdateWindow(hWnd);

    return 0;
}
