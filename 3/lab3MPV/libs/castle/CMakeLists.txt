add_library(castle_lib src/castle.cpp include/castle.h)

target_include_directories(castle_lib PUBLIC include)

#target_link_libraries(castle_lib)