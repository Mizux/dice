cmake_minimum_required(VERSION 3.4)
project(DiceGame)

##########################
##  INSTALL PARAMETERS  ##
##########################
# Offer the user the choice of overriding the installation directories
set(CMAKE_INSTALL_PREFIX install)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")

##############################
##  COMPILATION PARAMETERS  ##
##############################
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/share/doc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

#############
##  GCOVR  ##
#############
set(ENABLE_GCOV ON)
if(${ENABLE_GCOV})
	if(CMAKE_COMPILER_IS_GNUCXX) # gcc / gcov
		set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
		set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
		set(CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
		set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
		add_custom_target(coverage
			COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
			COMMAND ${CMAKE_COMMAND} -E make_directory coverage
			COMMAND ctest --output-on-failure
			COMMAND ../tools/gcovr --root=.. --delete
			--exclude ".*/test/.*" --exclude ".*/catch.hpp"
			--exclude ".*/moc_.*" --exclude ".*/qrc_.*"
			--html --html-details
			--output coverage/index.html
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
			COMMENT "Generating code coverage" VERBATIM)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang") # clang / llvm-cov gcov
		set(CMAKE_C_FLAGS "-g -O0 --coverage")
		set(CMAKE_CXX_FLAGS "-g -O0 --coverage")
		set(CMAKE_SHARED_LINKER_FLAGS "--coverage")
		set(CMAKE_EXE_LINKER_FLAGS "--coverage")
		add_custom_target(coverage
			COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
			COMMAND ${CMAKE_COMMAND} -E make_directory coverage
			COMMAND ctest --output-on-failure
			COMMAND ../tools/gcovr --root=.. --delete --use-llvm-cov
			--exclude ".*/test/.*" --exclude ".*/catch.hpp"
			--exclude ".*/moc_.*" --exclude ".*/qrc_.*"
			--html --html-details
			--output coverage/index.html
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
			COMMENT "Generating code coverage" VERBATIM)
	endif()
endif()

###########
##  DOC  ##
###########
add_subdirectory(doc)

############
##  TEST  ##
############
enable_testing()
add_subdirectory(Catch)

###############
##  LIBRARY  ##
###############
add_subdirectory(Dice)

############
##  APPS  ##
############
add_subdirectory(DiceApp)
