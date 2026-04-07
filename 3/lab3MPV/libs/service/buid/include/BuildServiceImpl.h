#pragma once
#include "castle/include/castle.h"
#include "map/include/map.h"
#include "model/service/build/BuildService.h"
#include "model/repository/towerRepo.h"
#include "model/service/build/TowerFactoryService.h"
#include "model/repository/towerTypeRegistry.h"

/**
 * реализация сервиса, для постройки башен
 */
class BuildServiceImpl: public BuildService {
    TowerRepository &towerRepo;
    TowerFactoryService &towerFactory;
    Map &map;
    Castle &castle;
    TowerTypeRegistry &towerTypeRegistry;

    public:
    BuildServiceImpl(TowerRepository &towerRepo, TowerFactoryService &towerFactory, Map &nMap, Castle &castle, TowerTypeRegistry &towerTypeReg);

    /**
     * @brief постройка башени
     * @param pos позичия для постройки
     * @param name имя в еестре башен
     * @return построили или нет
     */
    bool tryBuildTower(Point pos,const std::string& name) override;

    /**
     * @brief продажа бащни
     * @param tower укащатель на продоваемую башню
     */
    void sellTower(ITower *tower) override;

    /**
     * @brief квелечиние левелап башни
     * @param tower указаьедб на баштю
     * @return да или нет
     */
    bool levelUp(ITower *tower) override;

};