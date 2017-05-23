cmake_minimum_required(VERSION 3.2)
project(catch VERSION 1.9.4 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*.h")

add_library(Catch ${_HDRS})
set_target_properties(Catch PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Catch PUBLIC include)
