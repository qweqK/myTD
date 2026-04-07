add_library(defaultTower INTERFACE Tower.h)
target_link_libraries(defaultTower INTERFACE atackStrategy targetFindStrategy build)

add_library(magickEffect INTERFACE Magick.h)

add_library(trap INTERFACE Trap.h)

add_library(shoot INTERFACE Shoot.h)
target_link_libraries(shoot INTERFACE )

add_library(damage INTERFACE Damage.h)