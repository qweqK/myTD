#pragma once
#include "enemyServiceImpl.h"
#include "towerServiceImpl.h"
#include "model/service/game/GameService.h"
#include "castle/include/castle.h"

/**
 * @brief класс, реализующий логику игры
 */
class GameServiceImpl : public GameService {
    EnemyService &enemyService;
    TowerService &towerService;
    Castle & castle;
    TowerRepository & towers;
    EnemyRepo & enemies;


    public:
    explicit GameServiceImpl(EnemyService &enemyService_, TowerService &towerService_, Castle &castle_, TowerRepository &towers_, EnemyRepo &enemies_);
    void updateGame(float dt) override; ///< обноввить игару
    Game checkGameState() override; ///< ПРОВЕРКА СОСТОЯНИЯ ИГРЫ
    void removeTrash() override; ///< ПОЧМСТИТЬ УМЕРЩХ
};
