
cmake_minimum_required(VERSION 3.2)

project("Term++")

find_path(PROJECT_DIRECTORY src .. NO_DEFAULT_PATH)

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIRECTORY ${SOURCE_DIRECTORY}/include)
set(INSTALL_DIRECTORY ${PROJECT_DIRECTORY}/bin)

include_directories(${INCLUDE_DIRECTORY})

add_subdirectory(loader)
add_subdirectory(lib)
