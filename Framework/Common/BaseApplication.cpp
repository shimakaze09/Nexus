//
// Created by John on 27/07/2024
//

#include "BaseApplication.hpp"

#include <iostream>

using namespace Nexus;

bool Nexus::BaseApplication::m_bQuit = false;

Nexus::BaseApplication::BaseApplication(GfxConfiguration& cfg)
    : m_Config(cfg) {}

// Parse command line, read configuration, initialize all sub modules
int Nexus::BaseApplication::Initialize() {
    int result = 0;

    std::cout << m_Config;

    return result;
}

// Finalize all submodules and clean up all runtime temporary files.
void Nexus::BaseApplication::Finalize() {}

// One cycle of the main loop
void Nexus::BaseApplication::Tick() {}

bool Nexus::BaseApplication::IsQuit() { return m_bQuit; }
