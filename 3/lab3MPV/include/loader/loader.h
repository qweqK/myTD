#pragma once
#include "castle/include/castle.h"
#include "model/repository/effectRegistry.h"
#include "model/repository/towerRepo.h"
#include "map/include/map.h"
#include "mapper/enemyMapper.h"
#include "mapper/towerMapper.h"
#include "model/repository/attackRegistry.h"
#include "model/repository/enemyTypeRegistry.h"
#include "model/repository/findTargetRegistry.h"
#include "model/repository/lairRepo.h"
#include "model/repository/towerTypeRegistry.h"
#include "model/service/build/BuildService.h"
#include "model/service/build/TowerFactoryService.h"
#include "model/service/game/enemyService.h"
#include "model/service/game/GameService.h"
#include "model/service/game/PathCalcService.h"
#include "model/service/game/TowerService.h"
#include "model/service/load/configService.h"
#include "model/service/load/StateService.h"

class EnemyRepo;
/*
@класс для загрузки и выдачи всех компонентов, сервисов репозиториев и тд
 */
class loader {
    public:




    virtual ~loader()=default;
    virtual EnemyRepo & getEnemyRepo()=0;

    virtual TowerRepository & getTowerRepo()=0;

    virtual EffectRegistry & getEffectRegistry()=0;

    virtual Castle & getCastle()=0;

    virtual Map & getMap()=0;

    virtual AttackRegistry & getAttackRegistry() =0;

    virtual FindTargetRegistry &getFindRegistry() =0;

    virtual TowerMapper & getTowerMapper()=0;

    virtual EnemyMapper & getEnemyMapper()=0;

    virtual EnemyService & getEnemyService()=0;

    virtual TowerService & getTowerService()=0;

    virtual LairRepository &getLairRepository()=0;

    virtual BuildService &getBuildService ()=0;

    virtual GameService & getGameService()=0;

    virtual PathCalcService & getPathService()=0;

    virtual StateService & getStateService()=0;

    virtual TowerFactoryService & getTowerFactoryService() =0;

    virtual EnemyTypeRegistry & getEnemyTypeRegistry()=0;

    virtual TowerTypeRegistry & getTowerTypeRegistry()=0;

    virtual configLoadService & getConfigLoadService()=0;

    // virtual GraphicView & getGraphicView()=0;

    virtual Controller & getController()=0;

};
