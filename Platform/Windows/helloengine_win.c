//
// Created by John on 29/07/2024.
//

// Include basic Windows libraries
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

// The WindowProc function prototype
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// The entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    // The handle for the window, filled by a function
    HWND hWnd;
    // This struct holds information for the window class
    WNDCLASSEX wc;

    // Clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // Fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WinProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    // Register the window class
    RegisterClassEx(&wc);

    // Create the window and use the result as the handle
    hWnd = CreateWindowEx(0,
                          _T("WindowClass1"),    // name of the window class
                          _T("Hello, Engine!"),  // title of the window
                          WS_OVERLAPPEDWINDOW,   // window style
                          300,                   // x-position of the window
                          300,                   // y-position of the window
                          500,                   // width of the window
                          400,                   // height of the window
                          NULL,       // we have no parent window, NULL
                          NULL,       // we aren't using menus, NULL
                          hInstance,  // application handle
                          NULL);      // used with multiple windows, NULL

    // Display the window on the screen
    ShowWindow(hWnd, nCmdShow);

    // Enter the main loop:

    // This struct holds Windows event messages
    MSG msg;

    // Wait for the next message in the queue, store the result in 'msg'
    while (GetMessage(&msg, NULL, 0, 0)) {
        // Translate keystroke messages into the right format
        TranslateMessage(&msg);

        // Send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    // Return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// This is the main message handler for the program
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    // Sort through and find what code to run for the message given
    switch (message) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rec = {20, 20, 70, 80};
            HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);

            FillRect(hdc, &rec, brush);

            EndPaint(hWnd, &ps);
        } break;
        // This message is read when the window is closed
        case WM_DESTROY: {
            // Close the window
            PostQuitMessage(0);
            return 0;
        } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}
