add_library(base_tower include/baseTower.h src/baseTower.cpp include/baseTowerMapper.h src/baseTowerMapper.cpp)
target_include_directories(base_tower PUBLIC include)
target_link_libraries(base_tower defaultTower damage shoot targetFindStrategy atackStrategy attack_reg find_target_reg)
