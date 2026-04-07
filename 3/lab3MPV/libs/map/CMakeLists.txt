add_library(map_lib src/map.cpp include/map.h)

target_include_directories(map_lib PUBLIC include)
target_link_libraries(map_lib cell_lib matrix)