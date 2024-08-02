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
    explicit WindowsApplication(GfxConfiguration& config) : BaseApplication(config) {}

    int Initialize() override;
    void Finalize() override;

    void Tick() override;

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                                       LPARAM lParam);
};
}  // namespace Nexus

#endif  // NEXUS_WINDOWSAPPLICATION_HPP
