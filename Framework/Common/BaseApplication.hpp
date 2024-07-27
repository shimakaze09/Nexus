//
// Created by John on 27/07/2024
//

#ifndef FRAMEWORK_COMMON_BASEAPPLICATION_HPP
#define FRAMEWORK_COMMON_BASEAPPLICATION_HPP

#include "IApplication.hpp"

namespace Nexus {
class BaseApplication : implements IApplication {
   public:
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Tick() override;

    virtual bool IsQuit() override;

   protected:
    bool m_bQuit;
};
}  // namespace Nexus

#endif  // FRAMEWORK_COMMON_BASEAPPLICATION_HPP
