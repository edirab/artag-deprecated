#message(FATAL_ERROR "This option is not available for the moment")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})
add_executable(cameracalib camera_calibration.cpp)
target_link_libraries(cameracalib ${OpenCV_LIBRARIES} ARToolKitPlus)
