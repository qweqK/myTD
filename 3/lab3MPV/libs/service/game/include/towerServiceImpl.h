#pragma once
#include "map/include/map.h"
#include "model/repository/enemyRepo.h"
#include "model/repository/towerRepo.h"
#include "model/service/game/TowerService.h"

/**
 * @brief сервис, для обновления, логики башни
 */
class TowerServiceImpl : public TowerService{
    TowerRepository & towers;
    Map & map;
    EnemyRepo & enemies;
    public:
    TowerServiceImpl(TowerRepository & towers_, Map & map_ , EnemyRepo & enemies);
    void updateTower(float dt) override;///< обновить башни(сделать выстрел)
};
