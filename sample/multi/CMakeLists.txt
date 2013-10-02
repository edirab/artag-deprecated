add_executable(multi src/main.cpp)
target_link_libraries(multi ARToolKitPlus)

file(GLOB DATA_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/data data/*)
foreach(DATA ${DATA_FILES})
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
	configure_file(data/${DATA} ${CMAKE_CURRENT_BINARY_DIR}/data/${DATA} COPYONLY)
endforeach(DATA DATA_FILES)
