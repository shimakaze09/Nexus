//
// Created by John on 27/07/2024
//

#include "BaseApplication.hpp"

int Nexus::BaseApplication::Initialize() {
    m_bQuit = false;
    return 0;
}

void Nexus::BaseApplication::Finalize() {}

void Nexus::BaseApplication::Tick() {}

bool Nexus::BaseApplication::IsQuit() { return m_bQuit; }
