add_library(lair_repo_mem include/lairRepoMem.h src/lairRepoMem.cpp)
target_include_directories(lair_lib PUBLIC include)
target_link_libraries(lair_repo_mem lair_lib lair_repo)

add_library(tower_repo_mem include/towerRepoMem.h src/towerRepoMem.cpp)
target_include_directories(tower_repo_mem PUBLIC include)
target_link_libraries(tower_repo_mem tower_repo defaultTower)

add_library(enemy_repo_mem include/enemyRepoMem.h src/enemyRepoMem.cpp)
target_link_libraries(enemy_repo_mem enemy_repo enemy)
target_include_directories(enemy_repo_mem PUBLIC include)

