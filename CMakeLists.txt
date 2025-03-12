# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# @author      Eduardo Aguiar <aguiar@protonmail.ch>
# @copyright   Copyright (c) 2025 Eduardo Aguiar
#
# This file is part of Allegro++.
# 
# Allegro++ is free software: you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with Allegro++. If not, see <https://www.gnu.org/licenses/>.
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
cmake_minimum_required(VERSION 3.10)
project(Allegropp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Find Allegro using pkg-config or find_package
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
find_package(PkgConfig QUIET)

if (PKG_CONFIG_FOUND)
    pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    include_directories(${ALLEGRO_INCLUDE_DIRS})
    link_directories(${ALLEGRO_LIBRARY_DIRS})
else()
    # Fallback to find_package for Windows or if pkg-config is not available
    find_package(allegro5 REQUIRED COMPONENTS main image font ttf audio acodec)
    if (allegro5_FOUND)
        include_directories(${allegro5_INCLUDE_DIRS})
        link_directories(${allegro5_LIBRARY_DIRS})
    else()
        message(FATAL_ERROR "Allegro library not found. Please install Allegro 5.x.")
    endif()
endif()

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Set source files
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
set(SOURCES
    src/allegropp/bitmap.cpp
    src/allegropp/color.cpp
    src/allegropp/display.cpp
    src/allegropp/event_queue.cpp
    src/allegropp/event_source.cpp
    src/allegropp/font.cpp
    src/allegropp/keyboard.cpp
    src/allegropp/mouse.cpp
    src/allegropp/sample.cpp
    src/allegropp/timer.cpp
)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Define target
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
add_library(allegropp SHARED ${SOURCES})

set_target_properties(allegropp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(allegropp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Link Allegro libraries
if (PKG_CONFIG_FOUND)
    target_link_libraries(allegropp ${ALLEGRO_LIBRARIES})
else()
    target_link_libraries(allegropp allegro::allegro allegro::allegro_image allegro::allegro_font allegro::allegro_ttf allegro::allegro_audio allegro::allegro_acodec)
endif()

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Installation
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
install(TARGETS allegropp
    EXPORT allegroppTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/allegropp
)
install(DIRECTORY include/ DESTINATION include/allegropp)

install(EXPORT allegroppTargets
    FILE allegroppConfig.cmake
    NAMESPACE allegropp::
    DESTINATION lib/cmake/allegropp
)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Install a version file for the library
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    allegroppConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/allegroppConfigVersion.cmake
    DESTINATION lib/cmake/allegropp
)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Add example executable
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
if (BUILD_EXAMPLES)
    add_executable(example src/example.cpp)
    target_link_libraries(example allegropp)
    install(TARGETS example DESTINATION bin)
endif()
