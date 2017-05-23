cmake_minimum_required(VERSION 3.2)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	if(NOT DEFINED CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY)
    set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
  endif()

  file(GLOB _SRCS "*.dox" "*.dot")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  file(MAKE_DIRECTORY "${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}/${PROJECT_NAME}")
	add_custom_target(${PROJECT_NAME}_doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		SOURCES Doxyfile.in ${_SRCS}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
endif()
