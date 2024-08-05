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
    BaseApplication(GfxConfiguration& cfg);
    int Initialize() override;
    void Finalize() override;
    // One cycle of the main loop
    void Tick() override;

    bool IsQuit() override;

    inline GfxConfiguration& GetConfiguration() override { return m_Config; };

   protected:
    // Flag if we need to quit the main loop of the application
    static bool m_bQuit;
    GfxConfiguration m_Config;

   private:
    // Hide the default construct to enforce a configuration
    BaseApplication() = default;
};
}  // namespace Nexus

#endif  // FRAMEWORK_COMMON_BASEAPPLICATION_HPP
