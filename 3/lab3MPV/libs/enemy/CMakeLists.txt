add_library(base_enemy src/baseEnemy.cpp include/baseEnemyMapper.h include/BaseEnemy.h src/baseEnemyMapper.cpp)

target_include_directories(base_enemy PUBLIC include)

target_link_libraries(base_enemy enemy)