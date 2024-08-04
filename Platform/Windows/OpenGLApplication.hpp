//
// Created by John on 3/08/2024.
//

#ifndef NEXUS_OPENGLAPPLICATION_HPP
#define NEXUS_OPENGLAPPLICATION_HPP

#include "WindowsApplication.hpp"

namespace Nexus {
class OpenGLApplication : public WindowsApplication {
   public:
    explicit OpenGLApplication(GfxConfiguration& config) : WindowsApplication(config) {}

    int Initialize() override;
    void Finalize() override;

    void Tick() override;

   private:
    HGLRC m_RenderContext{};
};
}  // namespace Nexus

#endif  // NEXUS_OPENGLAPPLICATION_HPP
