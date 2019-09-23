cmake_minimum_required(VERSION 3.14)
project(UnnecessaryEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty)
add_subdirectory(engine)
add_subdirectory(dummy_app)