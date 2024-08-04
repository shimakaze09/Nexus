//
// Created by John on 3/08/2024.
//

#ifndef NEXUS_OPENGLGRAPHICSMANAGER_HPP
#define NEXUS_OPENGLGRAPHICSMANAGER_HPP

#include "GraphicsManager.hpp"

namespace Nexus {
class OpenGLGraphicsManager : public GraphicsManager {
   public:
    virtual int Initialize() override;
    virtual void Finalize() override;

    virtual void Tick() override;
};
}  // namespace Nexus

#endif  // NEXUS_OPENGLGRAPHICSMANAGER_HPP
