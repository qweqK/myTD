add_library(loader INTERFACE loader.h)
target_link_libraries(loader INTERFACE
        effect_reg
        enemy_repo
        tower_repo
        attack_reg
        find_target_reg
        buildService
        pathCalcService
        gameService
        enemyService
        enemyMapper
        enemyMapper
        )