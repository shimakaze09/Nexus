//
// Created by John on 29/07/2024.
//

#ifndef NEXUS_GRAPHICSMANAGER_HPP
#define NEXUS_GRAPHICSMANAGER_HPP

#include "IRuntimeModule.hpp"

namespace Nexus {
class GraphicsManager : implements IRuntimeModule {
   public:
    ~GraphicsManager() override = default;

    int Initialize() override;
    void Finalize() override;

    void Tick() override;
};
}  // namespace Nexus

#endif  // NEXUS_GRAPHICSMANAGER_HPP
