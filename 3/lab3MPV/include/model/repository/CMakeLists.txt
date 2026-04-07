add_library(crud INTERFACE REPO.h)
add_library(registry INTERFACE registry.h)

add_library(enemy_repo INTERFACE enemyRepo.h)
target_link_libraries(enemy_repo INTERFACE crud enemy)


add_library(tower_repo INTERFACE towerRepo.h)
target_link_libraries(tower_repo INTERFACE crud defaultTower)

add_library(lair_repo INTERFACE lairRepo.h)
target_link_libraries(lair_repo INTERFACE crud lair_lib)

add_library(attack_reg INTERFACE attackRegistry.h)
target_link_libraries(attack_reg INTERFACE registry atackStrategy)

add_library(find_target_reg INTERFACE findTargetRegistry.h)
target_link_libraries(find_target_reg INTERFACE registry targetFindStrategy)

add_library(effect_reg INTERFACE effectRegistry.h)
target_link_libraries(effect_reg INTERFACE registry effect)



add_library(enemy_type_registry INTERFACE enemyTypeRegistry.h)
target_link_libraries(enemy_type_registry INTERFACE enemy)

add_library(tower_type_registry INTERFACE towerTypeRegistry.h)
target_link_libraries(tower_type_registry INTERFACE defaultTower)



