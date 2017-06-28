
function(BUILD_DOXYGEN TARGET)
find_package(Doxygen)
if(DOXYGEN_FOUND)
	if(NOT DEFINED CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY)
    set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  file(GLOB _SRCS "*.dox" "*.dot")
  file(MAKE_DIRECTORY "${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}/${TARGET}")
	add_custom_target(${TARGET}_doc ALL
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 1 > /dev/null
		SOURCES Doxyfile.in ${_SRCS}
		DEPENDS ${ARGN}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating ${TARGET} doxygen documentation" VERBATIM
		)
	install(DIRECTORY ${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}/${TARGET} DESTINATION share/doc)
endif()
endfunction()
