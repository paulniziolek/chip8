cmake_minimum_required(VERSION 3.13)
project(chip8 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

# Packages
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

# TODO: include UT testing framework

# directories
include_directories(src)
include_directories(tests)

# exec
add_executable(chip8 src/main.cpp src/chip8.cpp src/instructions.cpp src/screen.cpp)
#add_executable(tests tests/*)

# link
target_link_libraries(chip8 PRIVATE spdlog::spdlog)
#target_link_options(chip8 PRIVATE -v)

# unit tests
#add_test(NAME my_test COMMAND example_test)
