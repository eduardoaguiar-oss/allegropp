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
cmake_minimum_required(VERSION 3.12)

project(AllegroPP
   VERSION 1.0.0
   DESCRIPTION "A modern C++ wrapper for the Allegro Game Library"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Define target
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
add_library(allegropp SHARED)

target_sources(allegropp
    PRIVATE
        src/allegropp/bitmap.cpp
        src/allegropp/color.cpp
        src/allegropp/display.cpp
        src/allegropp/event_queue.cpp
        src/allegropp/event_source.cpp
        src/allegropp/font.cpp
        src/allegropp/keyboard.cpp
        src/allegropp/mouse.cpp
        src/allegropp/sample.cpp
)

target_include_directories(allegropp
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        "src"
)

set_target_properties(allegropp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "allegropp"
)

set_property(TARGET allegropp PROPERTY POSITION_INDEPENDENT_CODE ON)

# Add compiler warnings (optional but recommended)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|MSVC")
    target_compile_options(allegropp PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
    )
endif()

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Find Allegro using pkg-config or find_package
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
find_package(PkgConfig QUIET)

if (PKG_CONFIG_FOUND)
    pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5 allegro_image-5)
    target_include_directories(allegropp PRIVATE ${ALLEGRO_INCLUDE_DIRS})
    target_link_directories(allegropp PRIVATE ${ALLEGRO_LIBRARY_DIRS})
    target_link_libraries(allegropp PUBLIC ${ALLEGRO_LIBRARIES})
else()
    # Fallback to find_package for Windows or if pkg-config is not available
    find_package(allegro5 REQUIRED COMPONENTS main image font ttf audio acodec)
    if (allegro5_FOUND)
        target_include_directories(allegropp PRIVATE ${allegro5_INCLUDE_DIRS})
        target_link_directories(allegropp PUBLIC ${allegro5_LIBRARY_DIRS})
        target_link_libraries(allegropp allegro::allegro allegro::allegro_image allegro::allegro_font allegro::allegro_ttf allegro::allegro_audio allegro::allegro_acodec)
    else()
        message(FATAL_ERROR "Allegro library not found. Please install Allegro 5.x.")
    endif()
endif()

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Installation
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
include(GNUInstallDirs)

install(TARGETS allegropp
    EXPORT allegroppTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install public headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/allegropp/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/allegropp
    FILES_MATCHING PATTERN "*.hpp"
)

# Export targets for downstream use
install(EXPORT allegroppTargets
    FILE AllegroPPTargets.cmake
    NAMESPACE AllegroPP::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AllegroPP
)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Install a version file for the library
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/AllegroPPConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(cmake/AllegroPPConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/AllegroPPConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/AllegroPPConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/AllegroPPConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AllegroPP
)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Package definition
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
set(CPACK_PACKAGE_NAME "Allegro++")
set(CPACK_PACKAGE_VENDOR "Eduardo Aguiar")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_SOURCE_GENERATOR "TXZ;ZIP")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_STRIP_FILES TRUE)
set(CPACK_SOURCE_IGNORE_FILES
    "/\\\\.git/"          # Git directory
    "/\\\\.github/"       # GitHub workflows
    "/build/"             # Build directory (case-sensitive)
    "/\\\\.cache/"        # Cache directories
    "\\\\.gitignore"      # Git ignore file
    "\\\\.DS_Store"       # macOS junk
    "\\\\.o$"             # Object files
    "\\\\.so$"            # Shared libraries
    "\\\\.a$"             # Static libraries
    "\\\\.dll$"           # Windows DLLs
    "\\\\.exe$"           # Executables
    "CMakeCache.txt"      # CMake cache
    "CMakeFiles/"         # CMake generated files
    "CPackConfig.cmake"   # CPack config
    "CPackSourceConfig.cmake"  # CPack source config
    "install_manifest.txt"     # Install manifest
    "Makefile"            # Generated Makefile
    "cmake_install.cmake" # CMake install script
)

include(CPack)

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Add example executable
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
if (BUILD_EXAMPLES)
    add_executable(example src/example.cpp)
    target_link_libraries(example allegropp)
    install(TARGETS example DESTINATION bin)
endif()
