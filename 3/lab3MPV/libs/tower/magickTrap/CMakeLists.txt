add_library(magick_trap include/magickTrap.h src/magickTrap.cpp src/magickTrapMapper.cpp include/magickTrapMapper.h)

target_include_directories(magick_trap PUBLIC include)
target_link_libraries(magick_trap defaultTower atackStrategy magickEffect effect_reg effect attack_reg)