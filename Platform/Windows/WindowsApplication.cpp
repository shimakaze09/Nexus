//
// Created by John on 2/08/2024.
//

#include "WindowsApplication.hpp"

#include <tchar.h>

using namespace Nexus;

int Nexus::WindowsApplication::Initialize() {
    int result;

    // First call base class initialization
    result = BaseApplication::Initialize();

    if (result != 0) exit(result);

    // Get the HINSTANCE of the Console Program
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // The handle for the window
    HWND hWnd;
    // This struct holds information for the window class
    WNDCLASSEX wc;

    // Clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // Fill in the struct with the necessary information
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
    hWnd = CreateWindowEx(0,
                          _T("NexusEngine"),      // name of the window class
                          m_Config.appName,       // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          CW_USEDEFAULT,          // x-position of the window
                          CW_USEDEFAULT,          // y-position of the window
                          m_Config.screenWidth,   // width of the window
                          m_Config.screenHeight,  // height of the window
                          nullptr,    // we have no parent window, NULL
                          nullptr,    // we aren't using menus, NULL
                          hInstance,  // application handle
                          nullptr);   // used with multiple windows, NULL

    // Display the window on the screen
    ShowWindow(hWnd, SW_SHOW);

    m_hWnd = hWnd;

    return result;
}

void Nexus::WindowsApplication::Finalize() {}

void Nexus::WindowsApplication::Tick() {
    // This struct holds Windows event messages
    MSG msg;

    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        // Translate keystroke messages into the right format
        TranslateMessage(&msg);

        // Send the message to the WindowProc function
        DispatchMessage(&msg);
    }
}

// This is the main message handler for the program
LRESULT CALLBACK Nexus::WindowsApplication::WindowProc(HWND hWnd, UINT message,
                                                       WPARAM wParam,
                                                       LPARAM lParam) {
    // Sort through and find what code to run for the message given
    switch (message) {
        case WM_PAINT: {
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
