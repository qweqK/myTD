#pragma once
#include "mapper/enemyMapper.h"
#include "mapper/towerMapper.h"
#include "model/repository/enemyTypeRegistry.h"
#include "model/repository/towerTypeRegistry.h"
#include "model/service/load/configService.h"

/**
 * класс, для загрузки начальных условий, из файла yaml
 */
class configLoadServiceImpl : public configLoadService {
    EnemyTypeRegistry & enemyTypes;
    TowerMapper& towerMapper;
    EnemyMapper& enemyMapper;
    TowerTypeRegistry & towerTypeRegistry;


    public:
    explicit configLoadServiceImpl(EnemyTypeRegistry & newRegTypes , TowerMapper & mapperT, EnemyMapper& mapperE, TowerTypeRegistry & towType) : enemyTypes(newRegTypes), towerMapper(mapperT), enemyMapper(mapperE), towerTypeRegistry(towType) {}
    void load(const std::string &path) override; ///< загрузка
};
