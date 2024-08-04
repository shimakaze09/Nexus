//
// Created by John on 3/08/2024.
//
#include <tchar.h>
#include "D3d/D3d12GraphicsManager.hpp"
#include "MemoryManager.hpp"
#include "WindowsApplication.hpp"

using namespace Nexus;

namespace Nexus {
GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540,
                        _T("Nexus Engine (Windows)"));
IApplication* g_pApp =
    static_cast<IApplication*>(new WindowsApplication(config));
GraphicsManager* g_pGraphicsManager =
    static_cast<GraphicsManager*>(new D3d12GraphicsManager);
MemoryManager* g_pMemoryManager =
    static_cast<MemoryManager*>(new MemoryManager);
}  // namespace Nexus
