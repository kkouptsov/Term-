
project(loader)

set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(HEADERS
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