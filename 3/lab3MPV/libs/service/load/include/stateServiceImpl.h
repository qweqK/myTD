#pragma once
#include "model/service/load/StateService.h"
#include "model/repository/towerRepo.h"
#include "model/repository/enemyRepo.h"
#include "model/repository/lairRepo.h"
#include  "map/include/map.h"
#include  "castle/include/castle.h"
#include "mapper/enemyMapper.h"
#include "mapper/towerMapper.h"
#include "model/repository/enemyTypeRegistry.h"

/**
 * @brief сервис, для загрузки и выгрузки в файлы, формата json
 */
class StateServiceImpl : public StateService {
    TowerRepository & towers;
    Map & map;
    EnemyRepo & enemies;
    Castle & castle;
    LairRepository & lairs;
    EnemyMapper & enemyMapper;
    TowerMapper & towerMapper;
    EnemyTypeRegistry & enemyTypes;
    public:
    explicit StateServiceImpl(TowerRepository & towers_, Map & map_, EnemyRepo& enemies_, Castle& castle_, LairRepository& lairs_, EnemyMapper& eMapper_, EnemyTypeRegistry & enemyTypes_ , TowerMapper & towerMapper_);
    void save(const std::string &path) override;
    void load(const std::string &path) override;
    void loadMap(const std::string &path) override;
    void loadEnemy(const std::string &path) override;
    void loadTower(const std::string &path) override;
    void loadCastle (const std::string &path) override;
    void loadLairs (const std::string &path) override;


};
