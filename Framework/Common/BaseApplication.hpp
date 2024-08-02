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
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Tick() override;

    virtual bool IsQuit() override;

   protected:
    // Flag if we need quit the main loop of the application
    static bool m_bQuit;
    GfxConfiguration m_Config;

   private:
    BaseApplication() = default;
};
}  // namespace Nexus

#endif  // FRAMEWORK_COMMON_BASEAPPLICATION_HPP
