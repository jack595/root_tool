cmake_minimum_required (VERSION 2.8)

project(plot)

aux_source_directory(. dir_plot)

add_definitions(-std=c++11)

# Find ROOT
find_package(ROOT QUIET)
if(NOT ROOT_FOUND)
	message(STATUS "ROOT package not found.")
	return()
endif()
include_directories(${ROOT_INCLUDE_DIRS})
#target_link_libraries(root-config --cflags --libs)
add_executable(plot ${dir_plot} ${ROOT_INCLUDE_DIRS})
