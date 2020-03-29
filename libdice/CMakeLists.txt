cmake_minimum_required(VERSION 3.8)
project(Dice VERSION 1.0 LANGUAGES CXX)
message(STATUS "project: ${PROJECT_NAME}")
message(STATUS "version: ${PROJECT_VERSION}")

add_subdirectory(doc)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*hxx")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(Dice "")
target_include_directories(Dice PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
target_sources(Dice
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/dice/Dice.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/dice/Die.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/dice/Face.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/dice/Roll.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/dice/Stat.hpp>
    $<INSTALL_INTERFACE:include/dice/Dice.hpp>
    $<INSTALL_INTERFACE:include/dice/Die.hpp>
    $<INSTALL_INTERFACE:include/dice/Face.hpp>
    $<INSTALL_INTERFACE:include/dice/Roll.hpp>
    $<INSTALL_INTERFACE:include/dice/Stat.hpp>
  PRIVATE
    ${_SRCS}
  )
#target_link_libraries(Dice)
target_compile_features(Dice PUBLIC cxx_std_11)
set_target_properties(Dice PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER $<TARGET_PROPERTY:Dice,INTERFACE_SOURCES>
  )
add_library(Dice::Dice ALIAS Dice)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

# Install
include(GNUInstallDirs)
install(TARGETS Dice
  EXPORT DiceTargets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dice
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT RUNTIME)
