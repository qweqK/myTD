#pragma once
#include "map/include/map.h"
#include "mapper/towerMapper.h"
#include "model/repository/towerRepo.h"
#include "model/service/build/TowerFactoryService.h"
#include "repo/registryMemory/include/towerTypeRegistryImpl.h"
#include "model/repository/towerTypeRegistry.h"

/**
 * реализация класса, для создания бащни
 */
class TowerFactoryImpl : public TowerFactoryService {
    Map &map;
    TowerRepository & towers;
    TowerTypeRegistry &towerTypeRegistry;
    public:
    explicit TowerFactoryImpl(Map &map, TowerRepository &repository, TowerTypeRegistry &towTypeRegistry);

    /**
     *
     * @param pos позмция создания
     * @param towerName имя в реестре
     */
    void create(Point pos,const std::string & towerName) const override;



};
