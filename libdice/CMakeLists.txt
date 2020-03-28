cmake_minimum_required(VERSION 3.8)
project(Dice CXX)

add_subdirectory(doc)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*hxx")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(Dice ${_HDRS} ${_SRCS})
#target_link_libraries(Dice)
target_include_directories(Dice PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
add_library(Dice::Dice ALIAS Dice)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

install(
  TARGETS Dice
  EXPORT DiceTargets
  DESTINATION lib
  COMPONENT RUNTIME)
