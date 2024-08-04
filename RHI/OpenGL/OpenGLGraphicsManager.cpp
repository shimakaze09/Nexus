//
// Created by John on 3/08/2024.
//

#include <stdio.h>

#include "OpenGLGraphicsManager.hpp"
#include "glad/glad.h"

using namespace Nexus;

int Nexus::OpenGLGraphicsManager::Initialize() {
    int result;

    result = gladLoadGL();
    if (!result) {
        printf("Failed to initialize OpenGL loader!\n");
        result = -1;
    } else {
        result = 0;
        printf("OpenGL Version %d.%d loaded\n", GLVersion.major,
               GLVersion.minor);

        if (GLAD_GL_VERSION_3_0) {
            // Set depth buffer to be entirely cleared to 1.0 values
            glClearDepth(1.0f);

            // Enable depth testing
            glEnable(GL_DEPTH_TEST);

            // Set the polygon winding to front facing
            glFrontFace(GL_CW);

            // Enable back face culling
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
    }

    return result;
}

void Nexus::OpenGLGraphicsManager::Finalize() {}

void Nexus::OpenGLGraphicsManager::Tick() {}
