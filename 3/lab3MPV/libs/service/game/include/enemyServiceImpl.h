#pragma once
#include "castle/include/castle.h"
#include "model/service/game/enemyService.h"
#include  "model/repository/enemyRepo.h"
#include "map/include/map.h"
#include "model/repository/effectRegistry.h"
#include "model/repository/lairRepo.h"

/**
 * реализация сервиса для врагов
 */
class EnemyServiceImpl : public EnemyService {
    EnemyRepo &enemyRepo;
    Map &map;
    //EffectRegistry &effectRegistry;
    LairRepository &lairRepo;
    Castle &castle;
    public:
    EnemyServiceImpl(EnemyRepo &enemyRepo, Map &map, LairRepository &lairRepo, Castle &castle);

    /**
     * @brief двиэжение- это верная смерть
     * @param dt время
     */
    void Move(float dt) override;

    /**
     * @brief жизнь- это спавн
     * @param dt время
     */
    void CreateAndSpawn(float dt) override;

    /**
     * @brief обновление врагов
     * @param dt дельтатайм
     */
    void update(float dt) override;


};
