//
// Created by John on 3/08/2024.
//

#ifndef NEXUS_D3D12GRAPHICSMANAGER_HPP
#define NEXUS_D3D12GRAPHICSMANAGER_HPP

#include <DXGI1_4.h>
#include <d3d12.h>
#include <cstdint>
#include "GraphicsManager.hpp"

namespace Nexus {
class D3d12GraphicsManager : public GraphicsManager {
   public:
    int Initialize() override;
    void Finalize() override;

    void Tick() override;

   private:
    HRESULT CreateRenderTarget();
    HRESULT CreateGraphicsResources();

   private:
    static const uint32_t kFrameCount = 2;
    ID3D12Device* m_pDev = nullptr;  // The pointer to the Direct3D device
    D3D12_VIEWPORT m_Viewport;       // Viewport structure
    D3D12_RECT m_ScissorRect;        // Scissor rectangle
    IDXGISwapChain3* m_pSwapChain = nullptr;        // Swap chain
    ID3D12Resource* m_pRenderTargets[kFrameCount];  // Render target buffer
    ID3D12CommandAllocator* m_pCommandAllocator = nullptr;  // Command allocator
    ID3D12CommandQueue* m_pCommandQueue = nullptr;          // Command queue
    ID3D12RootSignature* m_pRootSignature = nullptr;        // Root signature
    ID3D12DescriptorHeap* m_pRtvHeap = nullptr;             // Descriptor heap
    ID3D12PipelineState* m_pPipelineState =
        nullptr;  // Pipeline state object, it maintains the state of all the
                  // pipeline stages such as input assembler, rasterizer, shader
    ID3D12GraphicsCommandList* m_pCommandList = nullptr;  // Command list

    uint32_t m_nRtvDescriptorSize;

    ID3D12Resource* m_pVertexBuffer =
        nullptr;  // the pointer to the vertex buffer
    D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;  // a view of the vertex buffer

    // Synchronization objects
    uint32_t m_nFrameIndex;
    HANDLE m_hFenceEvent;
    ID3D12Fence* m_pFence = nullptr;
    uint32_t m_nFenceValue;
};
}  // namespace Nexus

#endif  // NEXUS_D3D12GRAPHICSMANAGER_HPP
