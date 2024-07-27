CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
SET(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)
PROJECT(Nexus)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/Framework/Common")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/Framework/Interface")
ADD_SUBDIRECTORY(Framework)
ADD_SUBDIRECTORY(Empty)