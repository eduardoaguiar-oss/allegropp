# CMakeLists.txt for examples subdirectory

# Define executable targets for each example
add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world PRIVATE allegropp)

# Install the executables to the specified directory
install(TARGETS hello_world #game_of_life labyrinth
    RUNTIME DESTINATION ${CMAKE_INSTALL_DATADIR}/allegropp/examples)
