//
// Created by John on 3/08/2024.
//

#include "D3d12GraphicsManager.hpp"
#include <d3dcompiler.h>
#include <objbase.h>
#include "WindowsApplication.hpp"

using namespace Nexus;

namespace Nexus {
extern IApplication* g_pApp;

template <class T>
inline void SafeRelease(T** ppInterfaceToRelease) {
    if (*ppInterfaceToRelease != nullptr) {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = nullptr;
    }
}

static void GetHardwareAdapter(IDXGIFactory4* pFactory,
                               IDXGIAdapter1** ppAdapter) {
    IDXGIAdapter1* pAdapter = nullptr;
    *ppAdapter = nullptr;

    for (UINT adapterIndex = 0;
         DXGI_ERROR_NOT_FOUND !=
         pFactory->EnumAdapters1(adapterIndex, &pAdapter);
         adapterIndex++) {
        DXGI_ADAPTER_DESC1 desc;
        pAdapter->GetDesc1(&desc);

        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            // Don't select the Basic Render Driver adapter.
            continue;
        }

        // Check to see if the adapter supports Direct3D 12, but don't create
        // the actual device yet.
        if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0,
                                        __uuidof(ID3D12Device), nullptr))) {
            break;
        }
    }

    *ppAdapter = pAdapter;
}
}  // namespace Nexus

HRESULT Nexus::D3d12GraphicsManager::CreateRenderTarget() {
    HRESULT hr;

    // Describe and create a render target view (RTV) descriptor heap.
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = kFrameCount;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    if (FAILED(hr = m_pDev->CreateDescriptorHeap(&rtvHeapDesc,
                                                 IID_PPV_ARGS(&m_pRtvHeap)))) {
        return hr;
    }

    m_nRtvDescriptorSize = m_pDev->GetDescriptorHandleIncrementSize(
        D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle =
        m_pRtvHeap->GetCPUDescriptorHandleForHeapStart();

    // Create an RTV for each frame.
    for (uint32_t i = 0; i < kFrameCount; i++) {
        if (FAILED(hr = m_pSwapChain->GetBuffer(
                       i, IID_PPV_ARGS(&m_pRenderTargets[i])))) {
            break;
        }
        m_pDev->CreateRenderTargetView(m_pRenderTargets[i], nullptr, rtvHandle);
        rtvHandle.ptr += m_nRtvDescriptorSize;
    }

    return hr;
}

HRESULT Nexus::D3d12GraphicsManager::CreateGraphicsResources() {
    HRESULT hr;

#if defined(_DEBUG)
    // Enable the D3D12 debug layer.
    {
        ID3D12Debug* pDebugController;
        if (SUCCEEDED(
                D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController)))) {
            pDebugController->EnableDebugLayer();
        }
        SafeRelease(&pDebugController);
    }
#endif

    IDXGIFactory4* pFactory;
    if (FAILED(hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory)))) {
        return hr;
    }

    IDXGIAdapter1* pHardwareAdapter;
    GetHardwareAdapter(pFactory, &pHardwareAdapter);

    if (FAILED(D3D12CreateDevice(pHardwareAdapter, D3D_FEATURE_LEVEL_11_0,
                                 IID_PPV_ARGS(&m_pDev)))) {
        IDXGIAdapter* pWarpAdapter;
        if (FAILED(
                hr = pFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)))) {
            SafeRelease(&pFactory);
            return hr;
        }

        if (FAILED(hr = D3D12CreateDevice(pWarpAdapter, D3D_FEATURE_LEVEL_11_0,
                                          IID_PPV_ARGS(&m_pDev)))) {
            SafeRelease(&pFactory);
            return hr;
        }
    }

    HWND hWnd = reinterpret_cast<WindowsApplication*>(g_pApp)->GetMainWindow();

    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    if (FAILED(hr = m_pDev->CreateCommandQueue(
                   &queueDesc, IID_PPV_ARGS(&m_pCommandQueue)))) {
        SafeRelease(&pFactory);
        return hr;
    }

    // Create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC1 scd;

    // Clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC1));

    // Fill the swap chain description struct
    scd.Width = g_pApp->GetConfiguration().screenWidth;
    scd.Height = g_pApp->GetConfiguration().screenHeight;
    scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // use 32-bit color
    scd.Stereo = FALSE;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = kFrameCount;
    scd.Scaling = DXGI_SCALING_STRETCH;
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain1* pSwapChain;
    if (FAILED(hr = pFactory->CreateSwapChainForHwnd(
                   m_pCommandQueue,  // Swap chain needs the queue so that it
                                     // can force a flush on it
                   hWnd, &scd, NULL, NULL, &pSwapChain))) {
        SafeRelease(&pFactory);
        return hr;
    }

    m_pSwapChain = reinterpret_cast<IDXGISwapChain3*>(pSwapChain);

    m_nFrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
    hr = CreateRenderTarget();

    return hr;
}

int Nexus::D3d12GraphicsManager::Initialize() {
    int result = 0;

    result = static_cast<int>(CreateGraphicsResources());

    return result;
}

void Nexus::D3d12GraphicsManager::Tick() {}

void Nexus::D3d12GraphicsManager::Finalize() {
    SafeRelease(&m_pFence);
    SafeRelease(&m_pVertexBuffer);
    SafeRelease(&m_pCommandList);
    SafeRelease(&m_pPipelineState);
    SafeRelease(&m_pRtvHeap);
    SafeRelease(&m_pRootSignature);
    SafeRelease(&m_pCommandQueue);
    SafeRelease(&m_pCommandAllocator);
    for (uint32_t i = 0; i < kFrameCount; i++) {
        SafeRelease(&m_pRenderTargets[i]);
    }
    SafeRelease(&m_pSwapChain);
    SafeRelease(&m_pDev);
}