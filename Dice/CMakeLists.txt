cmake_minimum_required(VERSION 3.2)
project(Dice CXX)

add_subdirectory(doc)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*hxx")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(${PROJECT_NAME} ${_HDRS} ${_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_subdirectory(test)

