//
// Created by John on 27/07/2024
//

#include "BaseApplication.hpp"

#include <iostream>

bool Nexus::BaseApplication::m_bQuit = false;

Nexus::BaseApplication::BaseApplication(GfxConfiguration& cfg)
    : m_Config(cfg) {}

int Nexus::BaseApplication::Initialize() {
    std::cout << m_Config;
    return 0;
}

void Nexus::BaseApplication::Finalize() {}

void Nexus::BaseApplication::Tick() {}

bool Nexus::BaseApplication::IsQuit() { return m_bQuit; }
