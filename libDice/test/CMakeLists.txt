set(NAME Dice_UT)

file(GLOB _SRCS "src/*.[hc]pp")

add_executable(${NAME} ${_SRCS})
target_link_libraries(${NAME} Catch2 Dice::Dice)
add_test(NAME ${NAME} COMMAND ${NAME})

if(${ENABLE_GCOV})
	set(GCOVR_OUTPUT_DIR ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/${PROJECT_NAME})
	add_custom_command(TARGET ${NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E remove_directory ${GCOVR_OUTPUT_DIR}
		COMMAND ${CMAKE_COMMAND} -E make_directory ${GCOVR_OUTPUT_DIR}
		COMMAND ctest --output-on-failure
		COMMAND ${GCOVR_PRG} --root=..
		--exclude ".*/Catch.hpp" --exclude=".*/test/"
		--exclude ".*App/.*" --exclude ".*/moc_.*" --exclude ".*/qrc_.*"
		COMMAND ${GCOVR_PRG} --root=.. --delete
		--exclude ".*/Catch.hpp" --exclude ".*/test/"
	 	--exclude ".*App/.*" --exclude ".*/moc_.*" --exclude ".*/qrc_.*"
		--html --html-details --output ${GCOVR_OUTPUT_DIR}/index.html
		DEPENDS ${NAME}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
