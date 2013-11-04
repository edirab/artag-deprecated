find_package(OpenCV REQUIRED)

include_directories(OpenCV_INCLUDE_DIRS)

##Copy any file in the data folder to the binary folder for the test sequence
#file(GLOB DATA_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/data data/*)
#foreach(DATA ${DATA_FILES})
#	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
#	configure_file(data/${DATA} ${CMAKE_CURRENT_BINARY_DIR}/data/${DATA} COPYONLY)
#endforeach(DATA DATA_FILES)
message("/!\\ Do no forget to create the symbolic link ${CMAKE_CURRENT_BINARY_DIR}/data to ${PROJECT_SOURCE_DIR}/astups/data")
message("\tIn Unix you can use \"ln -s ${CMAKE_CURRENT_BINARY_DIR}/data ${PROJECT_SOURCE_DIR}/astups/data\"")

add_executable(main main)
target_link_libraries(main ${OpenCV_LIBS} ARToolKitPlus)
