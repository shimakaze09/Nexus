//
// Created by John on 29/07/2024.
//

// Include basic Windows libraries
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include <d2d1.h>

ID2D1Factory *pFactory = nullptr;
ID2D1HwndRenderTarget *pRenderTarget = nullptr;
ID2D1SolidColorBrush *pLightSlateGrayBrush = nullptr;
ID2D1SolidColorBrush *pCornflowerBlueBrush = nullptr;

template <class T>
void SafeRelease(T **ppInterfaceToRelease) {
    if (*ppInterfaceToRelease) {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = nullptr;
    }
}

HRESULT CreateGraphicsResources(HWND hWnd) {
    HRESULT hr = S_OK;
    if (pRenderTarget == nullptr) {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size), &pRenderTarget);

        if (SUCCEEDED(hr)) {
            hr = pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                &pLightSlateGrayBrush);
        }

        if (SUCCEEDED(hr)) {
            hr = pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
                &pCornflowerBlueBrush);
        }
    }

    return hr;
}

void DiscardGraphicsResources() {
    SafeRelease(&pRenderTarget);
    SafeRelease(&pLightSlateGrayBrush);
    SafeRelease(&pCornflowerBlueBrush);
}

// The WindowProc function prototype
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// The entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    // The handle for the window, filled by a function
    HWND hWnd;
    // This struct holds information for the window class
    WNDCLASSEX wc;

    // Initialize COM
    if (FAILED(CoInitializeEx(
            nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
        return -1;

    // Clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // Fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WinProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    // Register the window class
    RegisterClassEx(&wc);

    // Create the window and use the result as the handle
    hWnd =
        CreateWindowEx(0,
                       _T("WindowClass1"),  // name of the window class
                       _T("Hello, Engine![Direct 2D]"),  // title of the window
                       WS_OVERLAPPEDWINDOW,              // window style
                       100,        // x-position of the window
                       100,        // y-position of the window
                       960,        // width of the window
                       540,        // height of the window
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
    while (GetMessage(&msg, nullptr, 0, 0)) {
        // Translate keystroke messages into the right format
        TranslateMessage(&msg);

        // Send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    // Uninitialize COM
    CoUninitialize();

    // Return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// This is the main message handler for the program
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    LRESULT result = 0;
    bool wasHandled = false;

    // Sort through and find what code to run for the message given
    switch (message) {
        case WM_CREATE:
            if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                                         &pFactory))) {
                result = -1;
                return result;
            }
            wasHandled = true;
            result = 0;
            break;
        case WM_PAINT: {
            HRESULT hr = CreateGraphicsResources(hWnd);
            if (SUCCEEDED(hr)) {
                PAINTSTRUCT ps;
                BeginPaint(hWnd, &ps);

                // Start build GPU draw commands
                pRenderTarget->BeginDraw();

                // Clear the window with white color
                pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

                // Retrieve the size of the drawing area
                D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

                // Draw a grid background
                int width = static_cast<int>(rtSize.width);
                int height = static_cast<int>(rtSize.height);

                for (int x = 0; x < width; x += 10) {
                    pRenderTarget->DrawLine(
                        D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                        D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                        pLightSlateGrayBrush, 0.5f);
                }

                for (int y = 0; y < height; y += 10) {
                    pRenderTarget->DrawLine(
                        D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                        D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
                        pLightSlateGrayBrush, 0.5f);
                }

                // Draw two rectangles
                D2D1_RECT_F rectangle1 = D2D1::RectF(
                    rtSize.width / 2 - 50.0f, rtSize.height / 2 - 50.0f,
                    rtSize.width / 2 + 50.0f, rtSize.height / 2 + 50.0f);

                D2D1_RECT_F rectangle2 = D2D1::RectF(
                    rtSize.width / 2 - 100.0f, rtSize.height / 2 - 100.0f,
                    rtSize.width / 2 + 100.0f, rtSize.height / 2 + 100.0f);

                // Draw a filled rectangle
                pRenderTarget->FillRectangle(&rectangle1, pLightSlateGrayBrush);

                // Draw the outline of a rectangle
                pRenderTarget->DrawRectangle(&rectangle2, pCornflowerBlueBrush);

                // End build GPU draw commands
                hr = pRenderTarget->EndDraw();
                if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
                    DiscardGraphicsResources();
                }

                EndPaint(hWnd, &ps);
            }
        }
            wasHandled = true;
            break;

        case WM_SIZE:
            if (pRenderTarget != nullptr) {
                RECT rc;
                GetClientRect(hWnd, &rc);

                D2D1_SIZE_U size =
                    D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
                pRenderTarget->Resize(size);
            }
            wasHandled = true;
            break;
        case WM_DESTROY:
            DiscardGraphicsResources();
            SafeRelease(&pFactory);
            PostQuitMessage(0);
            wasHandled = true;
            break;
        case WM_DISPLAYCHANGE:
            InvalidateRect(hWnd, nullptr, false);
            wasHandled = true;
            break;
    }

    // Handle any messages the switch statement didn't
    if (!wasHandled) {
        result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    return result;
}
