add_library(game_service_impl include/gameServiceImpl.h src/gameServiceImpl.cpp)
target_include_directories(game_service_impl PUBLIC include)

add_library(path_service_impl include/pathServiceImpl.h src/pathServiceImpl.cpp)
target_link_libraries(path_service_impl map_lib)
target_include_directories(path_service_impl PUBLIC include)

add_library(tower_service_impl include/towerServiceImpl.h src/towerServiceImpl.cpp)
target_include_directories(tower_service_impl PUBLIC include)

add_library(enemy_service_impl include/enemyServiceImpl.h src/enemyServiceImpl.cpp)
target_include_directories(enemy_service_impl PUBLIC include)




