//
// Created by John on 3/08/2024.
//

#ifndef NEXUS_OPENGLGRAPHICSMANAGER_HPP
#define NEXUS_OPENGLGRAPHICSMANAGER_HPP

#include "GraphicsManager.hpp"

namespace Nexus {
class OpenGLGraphicsManager : public GraphicsManager {
   public:
    int Initialize() override;
    void Finalize() override;

    void Tick() override;
};
}  // namespace Nexus

#endif  // NEXUS_OPENGLGRAPHICSMANAGER_HPP
