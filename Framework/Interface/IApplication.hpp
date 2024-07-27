//
// Created by John on 27/07/2024
//

#ifndef FRAMEWORK_INTERFACE_IAPPLICATION_HPP
#define FRAMEWORK_INTERFACE_IAPPLICATION_HPP

#include "IRuntimeModule.hpp"
#include "Interface.hpp"

namespace Nexus {
interface IApplication : implements IRuntimeModule {
   public:
    virtual int Initialize() = 0;
    virtual void Finalize() = 0;
    virtual void Tick() = 0;

    virtual bool IsQuit() = 0;
};
}  // namespace Nexus

#endif  // FRAMEWORK_INTERFACE_IAPPLICATION_HPP
