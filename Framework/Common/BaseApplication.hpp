//
// Created by John on 27/07/2024
//

#ifndef FRAMEWORK_COMMON_BASEAPPLICATION_HPP
#define FRAMEWORK_COMMON_BASEAPPLICATION_HPP

#include "GfxConfiguration.hpp"
#include "IApplication.hpp"

namespace Nexus {
class BaseApplication : implements IApplication {
   public:
    explicit BaseApplication(GfxConfiguration& cfg);
    int Initialize() override;
    void Finalize() override;
    // One cycle of the main loop
    void Tick() override;

    bool IsQuit() override;

   protected:
    // Flag if we need quit the main loop of the application
    static bool m_bQuit;
    GfxConfiguration m_Config;

   private:
    BaseApplication() = default;
};
}  // namespace Nexus

#endif  // FRAMEWORK_COMMON_BASEAPPLICATION_HPP
