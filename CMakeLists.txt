include_directories(${PROJECT_SOURCE_DIR}/root_tool/include)
include_directories(${PROJECT_SOURCE_DIR}/root_tool/src)
#file(GLOB root_tool_sources /home/luoxj/linux/soft/root_tool/src/*.cc)
#file(GLOB root_tool_headers /home/luoxj/linux/soft/root_tool/include/*.hh)
aux_source_directory(${PROJECT_SOURCE_DIR}/root_tool/include root_tool_headers)
aux_source_directory(${PROJECT_SOURCE_DIR}/root_tool/src root_tool_sources)

#add_library(ProjLib SHARED src/proj_lib.cc)
#target_include_directories(ProjLib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(root_tool SHARED ${root_tool_sources} ${root_tool_headers})
target_include_directories(root_tool PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
