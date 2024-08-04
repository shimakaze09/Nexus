ADD_EXECUTABLE(NexusEngineD3d12
        WindowsApplication.cpp
        D3d12Application.cpp
)

TARGET_LINK_LIBRARIES(NexusEngineD3d12 Common D3dRHI d3d12 dxgi d3dcompiler)

ADD_EXECUTABLE(NexusEngineOpenGL
        WindowsApplication.cpp
        OpenGLApplication.cpp
        ${PROJECT_SOURCE_DIR}/External/GL/src/glad_wgl.c
)

TARGET_LINK_LIBRARIES(NexusEngineOpenGL Common OpenGLRHI opengl32)
TARGET_INCLUDE_DIRECTORIES(NexusEngineOpenGL PRIVATE "${PROJECT_SOURCE_DIR}/External/GL/include")
