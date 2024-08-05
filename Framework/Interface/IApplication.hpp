//
// Created by John on 27/07/2024
//

#ifndef FRAMEWORK_INTERFACE_IAPPLICATION_HPP
#define FRAMEWORK_INTERFACE_IAPPLICATION_HPP

#include "GfxConfiguration.hpp"
#include "IRuntimeModule.hpp"

namespace Nexus {
interface IApplication : implements IRuntimeModule {
   public:
    int Initialize() override = 0;
    void Finalize() override = 0;
    void Tick() override = 0;

    virtual bool IsQuit() = 0;

    virtual GfxConfiguration& GetConfiguration() = 0;
};
}  // namespace Nexus

#endif  // FRAMEWORK_INTERFACE_IAPPLICATION_HPP
