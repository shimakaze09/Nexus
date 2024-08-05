//
// Created by John on 3/08/2024.
//

#include "OpenGLApplication.hpp"
#include <tchar.h>
#include <cstdio>
#include "MemoryManager.hpp"
#include "OpenGL/OpenGLGraphicsManager.hpp"
#include "glad/glad_wgl.h"

using namespace Nexus;

namespace Nexus {
GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540,
                        _T("Nexus Engine (Windows)"));
IApplication* g_pApp =
    static_cast<IApplication*>(new OpenGLApplication(config));
GraphicsManager* g_pGraphicsManager =
    static_cast<GraphicsManager*>(new OpenGLGraphicsManager);
MemoryManager* g_pMemoryManager =
    static_cast<MemoryManager*>(new MemoryManager);
}  // namespace Nexus

int Nexus::OpenGLApplication::Initialize() {
    int result;
    result = WindowsApplication::Initialize();
    if (result) {
        printf("Failed to initialize WindowsApplication\n");
    } else {
        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags =
            PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = m_Config.redBits + m_Config.greenBits +
                         m_Config.blueBits + m_Config.alphaBits;
        pfd.cDepthBits = m_Config.depthBits;
        pfd.iLayerType = PFD_MAIN_PLANE;

        HWND hWnd =
            reinterpret_cast<WindowsApplication*>(g_pApp)->GetMainWindow();
        if (!hWnd) {
            std::cout << "GetMainWindow Failed\n";
            return -1;
        }

        HDC hDC = GetDC(hWnd);
        if (!hDC) {
            std::cout << "GetDC Failed\n";
            return -1;
        }

        // Set temporary pixel format
        int nPixelFormat = ChoosePixelFormat(hDC, &pfd);
        if (nPixelFormat == 0) {
            std::cout << "ChoosePixelFormat Failed\n";
            return -1;
        }

        result = SetPixelFormat(hDC, nPixelFormat, &pfd);
        if (result != 1) {
            std::cout << "SetPixelFormat Failed\n";
            return -1;
        }

        // Create a temporary rendering context
        m_RenderContext = wglCreateContext(hDC);
        if (!m_RenderContext) {
            std::cout << "wglCreateContext Failed\n";
            return -1;
        }

        // Set the temporary rendering context as the current rendering context
        result = wglMakeCurrent(hDC, m_RenderContext);
        if (result != 1) {
            std::cout << "wglMakeCurrent Failed\n";
            return -1;
        }

        if (!gladLoadWGL(hDC)) {
            printf("Failed to initialize OpenGL loader!\n");
            return -1;
        } else {
            printf("WGL initialized\n");
            result = 0;
        }
    }

    return result;
}

void Nexus::OpenGLApplication::Finalize() {
    if (m_RenderContext) {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_RenderContext);
        m_RenderContext = nullptr;
    }
}

void Nexus::OpenGLApplication::Tick() { WindowsApplication::Tick(); }
