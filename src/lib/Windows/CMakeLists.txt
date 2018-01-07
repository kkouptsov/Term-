
project(library)

set(SOURCES
	${SOURCES}
	PARENT_SCOPE
)

set(HEADERS
	${HEADERS}
	PARENT_SCOPE
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
