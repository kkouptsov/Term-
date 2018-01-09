
project(library)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/console_impl.cpp
	PARENT_SCOPE
)

set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/console_impl.h
	PARENT_SCOPE
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
