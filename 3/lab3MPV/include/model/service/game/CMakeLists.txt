add_library(gameService INTERFACE GameService.h)

add_library(enemyService INTERFACE enemyService.h)
target_link_libraries(enemyService INTERFACE enemy dto)

add_library(pathCalcService INTERFACE PathCalcService.h)

add_library(towerService INTERFACE TowerService.h)
target_link_libraries(towerService INTERFACE defaultTower)