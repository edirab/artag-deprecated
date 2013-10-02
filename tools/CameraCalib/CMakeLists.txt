message(FATAL_ERROR "This option is not available for the moment")

file(GLOB CALIB_FILES src/*.cpp)
add_executable(cameracalib ${CALIB_FILES})
target_link_libraries(cameracalib ${OpenGL_LIBRARIES} ARToolKitPlus)
