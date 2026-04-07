add_library(cell_lib src/cell.cpp include/cell.h)

target_include_directories(cell_lib PUBLIC include)

target_link_libraries(cell_lib build enemy)