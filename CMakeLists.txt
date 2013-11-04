cmake_minimum_required(VERSION 2.6)
project(artag CXX)

set(CMAKE_CXX_FLAGs "-Wall")

set(APP_VERSION 2.1.1)

include_directories(${PROJECT_SOURCE_DIR}/include)

option(COMPILE_CALIB "Compile camera calibration tool, create a dependency to OpenGl" OFF)

if(COMPILE_CALIB)
	message(STATUS "Compile the camera calibration tool")
	find_package(OpenGL REQUIRED)
endif(COMPILE_CALIB)

add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(sample)
add_subdirectory(astups)

#Documentation
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
	file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/doc)
	configure_file(${PROJECT_SOURCE_DIR}/share/artag.doxy ${CMAKE_BINARY_DIR}/artag.doxy @only)
	add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/artag.doxy WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc COMMENT "Generating API documentation with Doxygen" VERBATIM)
else(DOXYGEN_FOUND)
	message(STATUS "Doxygen not found, so the documentation will not be generated")
endif(DOXYGEN_FOUND)

#Deinstall
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/share/uninstall.cmake.in ${CMAKE_BINARY_DIR}/uninstall.cmake IMMEDIATE @ONLY)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/uninstall.cmake)

