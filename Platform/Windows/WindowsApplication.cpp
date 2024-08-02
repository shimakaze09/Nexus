//
// Created by John on 2/08/2024.
//

#include "WindowsApplication.hpp"

#include <tchar.h>

using namespace Nexus;

namespace Nexus {
GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540,
                        L"Nexus Engine (Windows)");
WindowsApplication g_App(config);
IApplication* g_pApp = &g_App;
}  // namespace Nexus

int Nexus::WindowsApplication::Initialize() {
    int result;

    result = BaseApplication::Initialize();

    if (result != 0) exit(result);

    // Get the instance of console program
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // Create the handle of window
    HWND hWnd;
    // This struct holds information for the window class
    WNDCLASSEX wc;

    // Clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // Fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("NexusEngine");

    // Register the window class
    RegisterClassEx(&wc);

    // Create the window and use the result as the handle
    hWnd =
        CreateWindowExW(0,
                        L"GameEngineFromScratch",  // name of the window class
                        m_Config.appName,          // title of the window
                        WS_OVERLAPPEDWINDOW,       // window style
                        CW_USEDEFAULT,             // x-position of the window
                        CW_USEDEFAULT,             // y-position of the window
                        m_Config.screenWidth,      // width of the window
                        m_Config.screenHeight,     // height of the window
                        nullptr,    // we have no parent window, NULL
                        nullptr,    // we aren't using menus, NULL
                        hInstance,  // application handle
                        nullptr);   // used with multiple windows, NULL

    // Show the window on the screen
    ShowWindow(hWnd, SW_SHOW);

    return result;
}

void Nexus::WindowsApplication::Finalize() {}

void Nexus::WindowsApplication::Tick() {
    // This struct holds Windows event messages
    MSG msg;

    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK Nexus::WindowsApplication::WindowProc(HWND hWnd, UINT message,
                                                       WPARAM wParam,
                                                       LPARAM lParam) {
    // Sort through and find what code to run for the message given
    switch (message) {
        case WM_PRINT: {
        } break;

            // This message is read when the window is closed
        case WM_DESTROY: {
            // Close the application entirely
            PostQuitMessage(0);
            BaseApplication::m_bQuit = true;
            return 0;
        }
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}
