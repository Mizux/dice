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
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE _SRCS "src/*.[hc]pp")
file(GLOB_RECURSE _QRCS "data/*.qrc")

add_executable(DiceApp ${_SRCS} ${_QRCS})
target_link_libraries(DiceApp Dice::Dice Qt5::Core Qt5::Gui Qt5::Widgets)
install(
  TARGETS DiceApp
  EXPORT DiceTargets
  DESTINATION bin)
