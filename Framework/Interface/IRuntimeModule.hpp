//
// Created by John on 27/07/2024
//

#ifndef FRAMEWORK_INTERFACE_IRUNTIMEMODULE_HPP
#define FRAMEWORK_INTERFACE_IRUNTIMEMODULE_HPP

#include "Interface.hpp"

namespace Nexus {
_Interface_ IRuntimeModule {
   public:
    virtual ~IRuntimeModule() = default;

    virtual int Initialize() = 0;
    virtual void Finalize() = 0;

    virtual void Tick() = 0;
};
}  // namespace Nexus

#endif  // FRAMEWORK_INTERFACE_IRUNTIMEMODULE_HPP
