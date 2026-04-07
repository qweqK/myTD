add_library(static_loader src/static_loader.cpp include/static_loader.h)

target_include_directories(static_loader PUBLIC include)
target_link_libraries(static_loader
        loader
        base_tower
        base_enemy
        magick_trap
        magick_tower
        tower_factory_service_impl
        build_service_impl
        game_service_impl
        state_service_impl
        config_service_iml
        tower_repo_mem
        attack_registry_mem
        enemy_type_registry
        enemy_repo_mem
        attack_strategy_lib
        effectReal
        find_target_registry_mem
        effect_registry_mem
        shoot_strategy_lib
        lair_repo_mem
        path_service_impl
        tower_type_registry
        mapper
        enemyMapper
        towerMapper
        polymorphicMapper
        enemy_service_impl
        tower_type_registry_impl
        enemy_type_registry_mem
        tower_service_impl
        controller_impl
    )
