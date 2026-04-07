add_library(mapper INTERFACE mapper.h)


add_library(polymorphicMapper INTERFACE polymorphicMapper.h)
target_link_libraries(polymorphicMapper INTERFACE mapper)



add_library(towerMapper INTERFACE towerMapper.h)
target_link_libraries(towerMapper INTERFACE defaultTower polymorphicMapper mapper)


add_library(enemyMapper INTERFACE enemyMapper.h)
target_link_libraries(enemyMapper INTERFACE dto enemy polymorphicMapper mapper)


add_library(lairMapper INTERFACE lairMapper.h)
target_link_libraries(lairMapper INTERFACE dto lair_lib polymorphicMapper mapper)