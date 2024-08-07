CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
IF (${UNIX})
    SET(CMAKE_C_COMPILER "clang")
    SET(CMAKE_C_FLAGS_DEBUG "-g")
    SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
    SET(CMAKE_CXX_COMPILER "clang++")
    SET(CMAKE_CXX_FLAGS "-Wall")
    SET(CMAKE_CXX_FLAGS_DEBUG "-g")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
    SET(CMAKE_CXX_STANDARD 11)
ELSEIF (${WIN32})
    # Windows specific code
    SET(CMAKE_C_COMPILER "clang-cl")
    SET(CMAKE_C_FLAGS_DEBUG "/Debug /Zi")
    SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 /Debug")
    SET(CMAKE_CXX_COMPILER "clang-cl")
    SET(CMAKE_CXX_FLAGS_DEBUG "/Debug /Zi")
    SET(CMAKE_CXX_FLAGS "-Wall -Xclang -std=gnu++14")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 /Debug")
ENDIF (${UNIX})
SET(CMAKE_C_FLAGS "-Wall")
SET(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET(CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
SET(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

# --------------- Begin Generic CMake Variables Logging ---------------

# If you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise
# this is the top level directory of your build tree
MESSAGE(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# If you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this
# is the directory where the compiled or generated files from the current CMakeLists.txt will go to
MESSAGE(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

# This is the directory, from which cmake was started, i.e. the top level source directory
MESSAGE(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# This is the directory where the currently processed CMakeLists.txt is located in
MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

# Contains the full path to the top level directory of your build tree
MESSAGE(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

# Contains the full path to the root of your project source directory,
# i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command
MESSAGE(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

# Set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")

# Set this variable to specify a common place where CMake should put all libraries
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE(STATUS "LIBRARY_OUTPUT_PATH: ${LIBRARY_OUTPUT_PATH}")

# Tell CMake to search first in directories listed in CMAKE_MODULE_PATH
# when you use FIND_PACKAGE() or INCLUDE()
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

# This is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake)
MESSAGE(STATUS "CMAKE_COMMAND: ${CMAKE_COMMAND}")

# This is the CMake installation directory
MESSAGE(STATUS "CMAKE_ROOT: ${CMAKE_ROOT}")

# This is the filename including the complete path of the file where this variable is used.
MESSAGE(STATUS "CMAKE_CURRENT_LIST_FILE: ${CMAKE_CURRENT_LIST_FILE}")

# This is line number where the variable is used
MESSAGE(STATUS "CMAKE_CURRENT_LIST_LINE: ${CMAKE_CURRENT_LIST_LINE}")

# This is used when searching for include files e.g. using the FIND_PATH() command.
MESSAGE(STATUS "CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")

# This is used when searching for libraries e.g. using the FIND_LIBRARY() command.
MESSAGE(STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")

# The complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1"
MESSAGE(STATUS "CMAKE_SYSTEM: ${CMAKE_SYSTEM}")

# The short system name, e.g. "Linux", "FreeBSD" or "Windows"
MESSAGE(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

# Only the version part of CMAKE_SYSTEM
MESSAGE(STATUS "CMAKE_SYSTEM_VERSION: ${CMAKE_SYSTEM_VERSION}")

# The processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz")
MESSAGE(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")

# Is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
MESSAGE(STATUS "UNIX: ${UNIX}")

# Is TRUE on Windows, including CygWin
MESSAGE(STATUS "WIN32: ${WIN32}")

# Is TRUE on Apple OS X
MESSAGE(STATUS "APPLE: ${APPLE}")

# Is TRUE when using the MinGW compiler in Windows
MESSAGE(STATUS "MINGW: ${MINGW}")

# Is TRUE on Windows when using the CygWin version of cmake
MESSAGE(STATUS "CYGWIN: ${CYGWIN}")

# Is TRUE on Windows when using a Borland compiler
MESSAGE(STATUS "BORLAND: ${BORLAND}")

# Microsoft compiler
MESSAGE(STATUS "MSVC: ${MSVC}")
MESSAGE(STATUS "MSVC_IDE: ${MSVC_IDE}")
MESSAGE(STATUS "MSVC60: ${MSVC60}")
MESSAGE(STATUS "MSVC70: ${MSVC70}")
MESSAGE(STATUS "MSVC71: ${MSVC71}")
MESSAGE(STATUS "MSVC80: ${MSVC80}")
MESSAGE(STATUS "CMAKE_COMPILER_2005: ${CMAKE_COMPILER_2005}")


# Set this to true if you don't want to rebuild the object files if the rules have changed,
# but not the actual source files or headers (e.g. if you changed the some compiler switches)
MESSAGE(STATUS "CMAKE_SKIP_RULE_DEPENDENCY: ${CMAKE_SKIP_RULE_DEPENDENCY}")

# Since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing.
# If you don't like this, set this one to true.
MESSAGE(STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY}")

# If set, runtime paths are not added when using shared libraries. Default it is set to OFF
MESSAGE(STATUS "CMAKE_SKIP_RPATH: ${CMAKE_SKIP_RPATH}")

# Set this to true if you are using makefiles and want to see the full compile and link
# commands instead of only the shortened ones
MESSAGE(STATUS "CMAKE_VERBOSE_MAKEFILE: ${CMAKE_VERBOSE_MAKEFILE}")

# This will cause CMake to not put in the rules that re-run CMake. This might be useful if
# you want to use the generated build files on another machine.
MESSAGE(STATUS "CMAKE_SUPPRESS_REGENERATION: ${CMAKE_SUPPRESS_REGENERATION}")


# A simple way to get switches to the compiler is to use ADD_DEFINITIONS().
# But there are also two variables exactly for this purpose:

# The compiler flags for compiling C sources
MESSAGE(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

# The compiler flags for compiling C++ sources
MESSAGE(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug)
MESSAGE(STATUS "CMAKE_BUILD_TYPE:  ${CMAKE_BUILD_TYPE}")

# If this is set to ON, then all libraries are built as shared libraries by default.
MESSAGE(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

# The compiler used for C files
MESSAGE(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")

# The compiler used for C++ files
MESSAGE(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

# If the compiler is a variant of gcc, this should be set to 1
MESSAGE(STATUS "CMAKE_COMPILER_IS_GNUCC: ${CMAKE_COMPILER_IS_GNUCC}")

# If the compiler is a variant of g++, this should be set to 1
MESSAGE(STATUS "CMAKE_COMPILER_IS_GNUCXX : ${CMAKE_COMPILER_IS_GNUCXX}")

# The tools for creating libraries
MESSAGE(STATUS "CMAKE_AR: ${CMAKE_AR}")
MESSAGE(STATUS "CMAKE_RANLIB: ${CMAKE_RANLIB}")

# --------------- End Generic CMake Variables Logging ---------------

PROJECT(Nexus)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/Framework/Common")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/Framework/Interface")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/RHI/")
IF (${UNIX})
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/Platform/Linux")
ELSEIF (${WIN32})
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/Platform/Windows")
ENDIF (${UNIX})
ADD_SUBDIRECTORY(Framework)
ADD_SUBDIRECTORY(Platform)
ADD_SUBDIRECTORY(RHI)
