
cmake_minimum_required(VERSION 3.2)

project(library)

if(WIN32)
	add_subdirectory(Windows)
endif(WIN32)
if(UNIX)
	add_subdirectory(Unix)
endif(UNIX)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/term.cpp
)

set(HEADERS
	${INCLUDE_DIRECTORY}/term.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(term SHARED ${SOURCES} ${HEADERS})

install(
	TARGETS term
	DESTINATION ${INSTALL_DIRECTORY}
)
