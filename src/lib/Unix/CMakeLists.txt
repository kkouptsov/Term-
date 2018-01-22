
project(library)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/screen_impl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
	PARENT_SCOPE
)

set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/utils.h
	PARENT_SCOPE
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
