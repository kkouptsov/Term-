
cmake_minimum_required(VERSION 3.2)

project(loader)

set(GCC_LIB_LOAD_LINK_FLAGS "-ldl")

if(WIN32)
	add_subdirectory(Windows)
endif(WIN32)
if(UNIX)
	add_subdirectory(Unix)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_LIB_LOAD_LINK_FLAGS}")
endif(UNIX)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(HEADERS
	${HEADERS}
	${INCLUDE_DIRECTORY}/term.h
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${LIBRARY_DIRECTORY}
)

add_executable(loader ${SOURCES} ${HEADERS})

install(
	TARGETS loader
	DESTINATION ${INSTALL_DIRECTORY}
)
