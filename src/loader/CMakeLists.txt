
cmake_minimum_required(VERSION 3.2)

project(loader)

set(GCC_LIB_LOAD_LINK_FLAGS "-ldl")

if(WIN32)
	add_subdirectory(Windows)
endif(WIN32)
if(UNIX)
	add_subdirectory(Unix)
	SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LIB_LOAD_LINK_FLAGS}" )
endif(UNIX)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

set(HEADERS
	${HEADERS}
	${INCLUDE_DIRECTORY}/terminal.h
	${CMAKE_CURRENT_SOURCE_DIR}/libload.h
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
