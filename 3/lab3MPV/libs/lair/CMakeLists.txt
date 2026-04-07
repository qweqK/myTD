add_library(lair_lib include/lair.h src/lair.cpp)

target_include_directories(lair_lib PUBLIC include)

target_link_libraries(lair_lib dto)