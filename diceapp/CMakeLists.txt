#add_subdirectory(docs)

# Qt Setting
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6Core)
if(Qt6Core_FOUND)
  find_package(Qt6Gui REQUIRED)
  find_package(Qt6Widgets REQUIRED)
  set(QT_LIBS Qt6::Core Qt6::Gui Qt6::Widgets)
else()
  find_package(Qt5Core REQUIRED)
  find_package(Qt5Gui REQUIRED)
  find_package(Qt5Widgets REQUIRED)
  set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets)
endif()

file(GLOB_RECURSE _SRCS "src/*.[hc]pp")
file(GLOB_RECURSE _QRCS "data/*.qrc")

add_executable(DiceApp ${_SRCS} ${_QRCS})
# note: macOS is APPLE and also UNIX !
if(APPLE)
	set_target_properties(DiceApp PROPERTIES
    INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX AND NOT APPLE)
	set_target_properties(DiceApp PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
target_link_libraries(DiceApp Dice::Dice ${QT_LIBS})
add_executable(${PROJECT_NAMESPACE}::DiceApp ALIAS DiceApp)

# Install
install(TARGETS DiceApp
  EXPORT DiceTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT RUNTIME
)
