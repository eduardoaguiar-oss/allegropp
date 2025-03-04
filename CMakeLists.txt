cmake_minimum_required(VERSION 3.10)
project(Allegropp VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Allegro using pkg-config (Unix-like systems) or find_package (Windows)
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

# Add source files
set(SOURCES
    font.cpp
    sample.cpp
#    image.cpp
#    display.cpp
#    keyboard.cpp
)

# Add executable or library
add_library(allegropp ${SOURCES})

# Link Allegro libraries
if (PKG_CONFIG_FOUND)
    target_link_libraries(allegropp ${ALLEGRO_LIBRARIES})
else()
    target_link_libraries(allegropp allegro::allegro allegro::allegro_image allegro::allegro_font allegro::allegro_ttf allegro::allegro_audio allegro::allegro_acodec)
endif()

# Install the library (optional)
install(TARGETS allegropp
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# Add an example executable (optional)
if (BUILD_EXAMPLES)
    add_executable(example src/example.cpp)
    target_link_libraries(example allegropp)
    install(TARGETS example DESTINATION bin)
endif()
