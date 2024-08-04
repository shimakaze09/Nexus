//
// Created by John on 3/08/2024.
//

#ifndef NEXUS_D3D12GRAPHICSMANAGER_HPP
#define NEXUS_D3D12GRAPHICSMANAGER_HPP

#include <DXGI1_4.h>
#include <d3d12.h>
#include <stdint.h>
#include "GraphicsManager.hpp"

namespace Nexus {
class D3d12GraphicsManager : public GraphicsManager {
   public:
    virtual int Initialize() override;
    virtual void Finalize() override;

    virtual void Tick() override;

   private:
    HRESULT CreateRenderTarget();
    HRESULT CreateGraphicsResources();

   private:
    static const uint32_t kFrameCount = 2;
    ID3D12Device* m_pDev = nullptr;  // The pointer to the Direct3D device
    D3D12_VIEWPORT m_pViewport;         // Viewport structure
    D3D12_RECT m_scissorRect;          // Scissor rectangle
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

    ID3D12Resource* m_pVertexBuffer = nullptr;    // Vertex buffer
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;  // Vertex buffer view

    // Synchronization objects
    uint32_t m_nFrameIndex;
    HANDLE m_fenceEvent;
    ID3D12Fence* m_pFence;
    uint64_t m_fenceValue;
};
}  // namespace Nexus

#endif  // NEXUS_D3D12GRAPHICSMANAGER_HPP
