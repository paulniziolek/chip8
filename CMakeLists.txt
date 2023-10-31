cmake_minimum_required(VERSION 3.10)
project(testing LANGUAGES CXX)
enable_testing()

# TODO: include UT testing framework

# directories
include_directories(src)
include_directories(tests)

# exec
add_executable(main src/*)
add_executable(tests tests/*)

# unit tests
#add_test(NAME my_test COMMAND example_test)
