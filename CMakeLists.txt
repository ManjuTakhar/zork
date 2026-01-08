cmake_minimum_required(VERSION 3.15)
project(Zork VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Room.cpp
    src/Item.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Command.cpp
    src/Utils.cpp
    src/SaveManager.cpp
)

# Header files
set(HEADERS
    include/Game.h
    include/Room.h
    include/Item.h
    include/Player.h
    include/Enemy.h
    include/Command.h
    include/Utils.h
    include/SaveManager.h
    include/Constants.h
)

# Main executable
add_executable(zork ${SOURCES} ${HEADERS})

# Installation
install(TARGETS zork DESTINATION bin)

# Copy data files
install(DIRECTORY data/ DESTINATION share/zork/data)

# Tests (optional)
option(BUILD_TESTS "Build test programs" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Package configuration
set(CPACK_PACKAGE_NAME "Zork")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A text-based adventure game")
set(CPACK_PACKAGE_VENDOR "Zork Development Team")
include(CPack)
