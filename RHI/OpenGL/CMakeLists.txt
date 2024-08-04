ADD_LIBRARY(OpenGLRHI
        OpenGLGraphicsManager.cpp
        ${PROJECT_SOURCE_DIR}/External/GL/src/glad.c
)

TARGET_INCLUDE_DIRECTORIES(OpenGLRHI PRIVATE "${PROJECT_SOURCE_DIR}/External/GL/include")
