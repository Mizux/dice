cmake_minimum_required(VERSION 3.20)
project(DiceApp VERSION 1.0 LANGUAGES CXX)
message(STATUS "Project: ${PROJECT_NAME}, version: ${PROJECT_VERSION}")
#message(STATUS "major: ${PROJECT_VERSION_MAJOR}")
#message(STATUS "minor: ${PROJECT_VERSION_MINOR}")
#message(STATUS "patch: ${PROJECT_VERSION_PATCH}")

add_subdirectory(docs)

# Qt Setting
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Widgets REQUIRED)

file(GLOB_RECURSE _SRCS "src/*.[hc]pp")
file(GLOB_RECURSE _QRCS "data/*.qrc")

add_executable(DiceApp ${_SRCS} ${_QRCS})
target_link_libraries(DiceApp Dice::Dice Qt6::Core Qt6::Gui Qt6::Widgets)
install(
  TARGETS DiceApp
  EXPORT DiceTargets
  DESTINATION bin)
