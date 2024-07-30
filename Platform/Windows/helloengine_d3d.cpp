//
// Created by John on 30/07/2024.
//

// Include basic Windows libraries
#include <stdint.h>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include <DirectXMath.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

using namespace DirectX;

const uint32_t SCREEN_WIDTH = 960;
const uint32_t SCREEN_HEIGHT = 480;

// Global declarations
IDXGISwapChain *g_pSwapChain = nullptr;
ID3D11Device *g_pDevice = nullptr;
ID3D11DeviceContext *g_pDeviceContext = nullptr;

ID3D11RenderTargetView *g_pRenderTargetView = nullptr;

ID3D11InputLayout *g_pVertexLayout = nullptr;
ID3D11VertexShader *g_pVertexShader = nullptr;
ID3D11PixelShader *g_pPixelShader = nullptr;

ID3D11Buffer *g_pVertexBuffer = nullptr;

// Vertex buffer structure
struct VERTEX {
    XMFLOAT3 Position;
    XMFLOAT4 Color;
};

template <class T>
void SafeRelease(T **ppInterfaceToRelease) {
    if (*ppInterfaceToRelease) {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = nullptr;
    }
}

void CreateRenderTarget() {
    ID3D11Texture2D *pBackBuffer;

    // Get the pointer to the back buffer
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                            (LPVOID *)&pBackBuffer);

    // Create a render target view
    g_pDevice->CreateRenderTargetView(pBackBuffer, nullptr,
                                      &g_pRenderTargetView);

    pBackBuffer->Release();

    // Bind the view
    g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);
}

void SetViewPort() {
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    g_pDeviceContext->RSSetViewports(1, &viewport);
}

// Load and prepare the shaders
void InitPipeline() {
    // Load and compile the two shaders
    ID3D10Blob *VS, *PS;
    D3DReadFileToBlob(L"copy.vso", &VS);
    D3DReadFileToBlob(L"copy.pso", &PS);

    // Encapsulate both shaders into shader objects
    g_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(),
                                  nullptr, &g_pVertexShader);
    g_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(),
                                 nullptr, &g_pPixelShader);

    // Set the shader objects
    g_pDeviceContext->VSSetShader(g_pVertexShader, nullptr, 0);
    g_pDeviceContext->PSSetShader(g_pPixelShader, nullptr, 0);

    // Create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
         D3D11_INPUT_PER_VERTEX_DATA, 0}};

    g_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(),
                                 VS->GetBufferSize(), &g_pVertexLayout);
    g_pDeviceContext->IASetInputLayout(g_pVertexLayout);

    VS->Release();
    PS->Release();
}

// Create the shape to render
void InitGraphics() {
    // Create a triangle using the VERTEX struct
    VERTEX OurVertices[] = {
        {XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
        {XMFLOAT3(0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
        {XMFLOAT3(-0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}};

    // Create the vertex buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(VERTEX) * 3;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    g_pDevice->CreateBuffer(&bd, nullptr, &g_pVertexBuffer);

    // Copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    g_pDeviceContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL,
                          &ms);
    memcpy(ms.pData, OurVertices, sizeof(OurVertices));
    g_pDeviceContext->Unmap(g_pVertexBuffer, 0);
}

// Prepare graphic resources
HRESULT CreateGraphicsResources(HWND hWnd) {
    HRESULT hr = S_OK;
    if (g_pSwapChain == nullptr) {
        // Create a struct to hold information about the swap chain
        DXGI_SWAP_CHAIN_DESC scd;

        // Clear out the struct for use
        ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

        // Fill the swap chain description struct
        scd.BufferCount = 1;                                 // one back buffer
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // use 32-bit color
        scd.BufferDesc.Width = SCREEN_WIDTH;    // set the back buffer width
        scd.BufferDesc.Height = SCREEN_HEIGHT;  // set the back buffer height
        scd.BufferDesc.RefreshRate.Numerator = 60;          // 60Hz refresh rate
        scd.BufferDesc.RefreshRate.Denominator = 1;         // 60Hz refresh rate
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // how swap chain is
                                                            // going to be used
        scd.OutputWindow = hWnd;   // the window going to be used
        scd.SampleDesc.Count = 4;  // how many multi-samples
        scd.Windowed = TRUE;       // windowed/full-screen mode
        scd.Flags =
            DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;  // allow full-screen
                                                     // switching

        const D3D_FEATURE_LEVEL FeatureLevels[] = {
            D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,  D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1};
        D3D_FEATURE_LEVEL FeatureLevelSupported;

        // Create the swap chain, device and device context
        hr = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, FeatureLevels,
            ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &scd, &g_pSwapChain,
            &g_pDevice, &FeatureLevelSupported, &g_pDeviceContext);

        if (hr == E_INVALIDARG) {
            hr = D3D11CreateDeviceAndSwapChain(
                nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
                &FeatureLevels[1], ARRAYSIZE(FeatureLevels) - 1,
                D3D11_SDK_VERSION, &scd, &g_pSwapChain, &g_pDevice,
                &FeatureLevelSupported, &g_pDeviceContext);
        }

        if (hr == S_OK) {
            CreateRenderTarget();
            SetViewPort();
            InitPipeline();
            InitGraphics();
        }
    }

    return hr;
}

void DiscardGraphicsResources() {
    SafeRelease(&g_pVertexLayout);
    SafeRelease(&g_pVertexShader);
    SafeRelease(&g_pPixelShader);
    SafeRelease(&g_pVertexBuffer);
    SafeRelease(&g_pSwapChain);
    SafeRelease(&g_pRenderTargetView);
    SafeRelease(&g_pDevice);
    SafeRelease(&g_pDeviceContext);
}

// Render the frame
void RenderFrame() {
    // Clear the back buffer
    const FLOAT clearColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);

    // 3D rendering on the back buffer
    {
        // Select which vertex buffer to display
        UINT stride = sizeof(VERTEX);
        UINT offset = 0;
        g_pDeviceContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride,
                                             &offset);

        // Select which primitive type we are using
        g_pDeviceContext->IASetPrimitiveTopology(
            D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Draw the vertex buffer to the back buffer
        g_pDeviceContext->Draw(3, 0);
    }

    // Present the back buffer to the screen
    g_pSwapChain->Present(0, 0);
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
                       _T("Hello, Engine![Direct 3D]"),  // title of the window
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
            wasHandled = true;
            break;
        case WM_PAINT:
            result = CreateGraphicsResources(hWnd);
            RenderFrame();
            wasHandled = true;
            break;
        case WM_SIZE:
            if (g_pSwapChain != nullptr) {
                DiscardGraphicsResources();
            }
            wasHandled = true;
            break;
        case WM_DESTROY:
            DiscardGraphicsResources();
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
