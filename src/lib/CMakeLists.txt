
cmake_minimum_required(VERSION 3.2)

project(library)

add_definitions(-DLIBRARY)

if(WIN32)
	add_subdirectory(Windows)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Windows)
endif(WIN32)
if(UNIX)
	add_subdirectory(Unix)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Unix)
endif(UNIX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/terminal.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/console.cpp
)

set(HEADERS
	${HEADERS}
	${INCLUDE_DIRECTORY}/terminal.h
	${INCLUDE_DIRECTORY}/config.h
	${CMAKE_CURRENT_SOURCE_DIR}/console.h
	${CMAKE_CURRENT_SOURCE_DIR}/except.h
	${CMAKE_CURRENT_SOURCE_DIR}/screen.h
)

add_library(term SHARED ${SOURCES} ${HEADERS})

install(
	TARGETS term
	DESTINATION ${INSTALL_DIRECTORY}
)
