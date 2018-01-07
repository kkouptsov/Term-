
project(loader)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/libload.c
	PARENT_SCOPE
)

set(HEADERS
	${HEADERS}
	PARENT_SCOPE
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
