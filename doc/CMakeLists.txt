# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	if(NOT DEFINED CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY)
    set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  file(GLOB _SRCS "*.dox" "*.dot")
  file(MAKE_DIRECTORY "${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}/${PROJECT_NAME}")
	add_custom_target(${PROJECT_NAME}_doc ALL
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 1 > /dev/null
		SOURCES Doxyfile.in ${_SRCS}
		DEPENDS Dice_doc DiceApp_doc
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
endif()
