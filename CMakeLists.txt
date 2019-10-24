cmake_minimum_required(VERSION 3.13)
project(UnnecessaryEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
include(cmake/Unnecessary.cmake)
cmake_policy(SET CMP0072 NEW)

add_subdirectory(thirdparty)
add_subdirectory(modules)
add_subdirectory(dummy_app)
