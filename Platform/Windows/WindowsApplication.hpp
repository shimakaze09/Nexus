//
// Created by John on 2/08/2024.
//

#ifndef NEXUS_WINDOWSAPPLICATION_HPP
#define NEXUS_WINDOWSAPPLICATION_HPP

#include "BaseApplication.hpp"

#include <windows.h>
#include <windowsx.h>

namespace Nexus {
class WindowsApplication : public BaseApplication {
   public:
    WindowsApplication(GfxConfiguration& config) : BaseApplication(config) {}

    virtual int Initialize() override;
    virtual void Finalize() override;

    virtual void Tick() override;

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                                       LPARAM lParam);
};
}  // namespace Nexus

#endif  // NEXUS_WINDOWSAPPLICATION_HPP
