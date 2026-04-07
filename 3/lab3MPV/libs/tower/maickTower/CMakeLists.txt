add_library(magick_tower src/magickTower.cpp include/magickTower.h src/magickTowerMapper.cpp include/magickTowerMapper.h)

target_include_directories(magick_tower PUBLIC include)

target_link_libraries(magick_tower damage magickEffect defaultTower shoot atackStrategy targetFindStrategy find_target_reg attack_reg effect_reg)