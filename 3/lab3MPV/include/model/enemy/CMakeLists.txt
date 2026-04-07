add_library(enemy INTERFACE Enemy.h)
target_link_libraries(enemy INTERFACE point)
target_link_libraries(enemy INTERFACE effect)