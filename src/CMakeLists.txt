add_library(ARToolKitPlus SHARED MemoryManager.cpp DLL.cpp librpp/rpp.cpp librpp/rpp_quintic.cpp librpp/rpp_vecmat.cpp librpp/rpp_svd.cpp librpp/librpp.cpp extra/Profiler.cpp extra/FixedPoint.cpp)
set_target_properties(ARToolKitPlus PROPERTIES VERSION ${APP_VERSION})

#Install the library
install(TARGETS ARToolKitPlus DESTINATION lib)


#Before installng the includes, some includes need to be fixed as the point to some other file (mainly in src)
set(BROKEN_HEADERS #src/core/arLabeling.cxx
		include/ARToolKitPlus/TrackerImpl.h
		include/ARToolKitPlus/TrackerMultiMarkerImpl.h
		include/ARToolKitPlus/TrackerSingleMarkerImpl.h)

foreach(BROKEN ${BROKEN_HEADERS})
	file(READ "${PROJECT_SOURCE_DIR}/${BROKEN}" RESULT)
	string(REGEX MATCHALL "src/[a-zA-Z0-9./]*" FILES_TO_INCLUDE ${RESULT})
	foreach(FILE_TO_INCLUDE ${FILES_TO_INCLUDE})
		if(EXISTS "${PROJECT_SOURCE_DIR}/${FILE_TO_INCLUDE}")
			file(READ "${PROJECT_SOURCE_DIR}/${FILE_TO_INCLUDE}" CONTENT)
			string(REPLACE "\#include \"../../${FILE_TO_INCLUDE}\"" "${CONTENT}" RESULT "${RESULT}")
		else(EXISTS "${PROJECT_SOURCE_DIR}/${FILE_TO_INCLUDE}")
			message(STATUS "WARNING: This file does not exist: ${PROJECT_SOURCE_DIR}/${FILE_TO_INCLUDE}\nBut is needed by: ${BROKEN}")
			string(REPLACE "#include \"../../${FILE_TO_INCLUDE}\"" "//#include \"../../${FILE_TO_INCLUDE}\"" RESULT "${RESULT}")
		endif(EXISTS "${PROJECT_SOURCE_DIR}/${FILE_TO_INCLUDE}")
	endforeach(FILE_TO_INCLUDE ${FILES_TO_INCLUDE})
	file(WRITE "${CMAKE_BINARY_DIR}/${BROKEN}" "${RESULT}")
endforeach(BROKEN ${BROKEN_HEADERS})

#Install the broken files
file(GLOB EX_BROKEN_HEADERS ${CMAKE_BINARY_DIR}/include/ARToolKitPlus/*.h)
install(FILES ${EX_BROKEN_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ARToolKitPlus/)

#Install the headers
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/ARToolKitPlus/*.h)
list(REMOVE_ITEM HEADERS ${BROKEN_HEADERS})
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ARToolKitPlus/)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/ARToolKitPlus/extra/*.h)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ARToolKitPlus/extra/)
