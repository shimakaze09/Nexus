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

    int Initialize() override;
    void Finalize() override;
    // One cycle of the main loop
    void Tick() override;

    // The WindowProc function prototype
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                                       LPARAM lParam);

    inline HWND GetMainWindow() { return m_hWnd; };

   private:
    HWND m_hWnd;
};
}  // namespace Nexus

#endif  // NEXUS_WINDOWSAPPLICATION_HPP
