cmake_minimum_required(VERSION 3.20)
project(Dice VERSION 1.0 LANGUAGES CXX)
message(STATUS "Project: ${PROJECT_NAME}, version: ${PROJECT_VERSION}")
#message(STATUS "major: ${PROJECT_VERSION_MAJOR}")
#message(STATUS "minor: ${PROJECT_VERSION_MINOR}")
#message(STATUS "patch: ${PROJECT_VERSION_PATCH}")

add_subdirectory(docs)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*hxx")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(Dice "")
target_include_directories(Dice PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
target_sources(Dice PRIVATE
  ${_HDRS}
  ${_SRCS}
)
#target_link_libraries(Dice)
target_compile_features(Dice PUBLIC cxx_std_11)
set_target_properties(Dice PROPERTIES
  VERSION ${PROJECT_VERSION}
  )
set_property(TARGET Dice PROPERTY
  PUBLIC_HEADER ${_HDRS}
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
