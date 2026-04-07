#pragma once
#include "controller/include/controllerImpl.h"
#include "loader/loader.h"
#include "model/repository/enemyTypeRegistry.h"
#include "model/repository/towerTypeRegistry.h"
#include "model/service/load/StateService.h"

/**
 * @brief статический загрузчик
 */
class StaticLoader : loader {
    std::unique_ptr<TowerService> towerService;
    std::unique_ptr<EnemyService> enemyService;
    std::vector<std::unique_ptr<SubtypeMapper<ITower, TowerDTO, std::unique_ptr<ITower>>>> towerSubtypeMappers;
    std::unique_ptr<TowerMapper> towMapper;
    std::vector<std::unique_ptr<SubtypeMapper<IEnemy, EnemyDto, std::unique_ptr<IEnemy>>>> enemiesSubtypeMappers;
    std::unique_ptr<EnemyMapper> enemyMapper;
    std::unique_ptr<TowerRepository> towRepo;
    std::unique_ptr<EnemyRepo> enemyRepo;
    std::unique_ptr<LairRepository> lairRepo;
    std::unique_ptr<AttackRegistry> attackRegistry;
    std::unique_ptr<EffectRegistry> effectRegistry;
    std::unique_ptr<FindTargetRegistry> findRegistry;
    std::unique_ptr<GameService> gameService;
    std::unique_ptr<PathCalcService> pathCalcService;
    std::unique_ptr<BuildService> buildService;
    std::unique_ptr<Castle> castle;
    std::unique_ptr<Map >map;
    std::unique_ptr<StateService> stateServiceLoader;
    std::unique_ptr<TowerFactoryService> towFactoryService;
    std::unique_ptr<TowerTypeRegistry> towerTypeRegistry;
    std::unique_ptr<EnemyTypeRegistry> enemyTypeRegistry;
    std::unique_ptr<configLoadService> cconfigLoadService;
    std::unique_ptr<Controller> controller;


    public:
     EnemyRepo & getEnemyRepo() override;

     TowerRepository & getTowerRepo() override;

     EffectRegistry & getEffectRegistry() override;

     Castle & getCastle() override;

     Map & getMap() override;

     AttackRegistry & getAttackRegistry() override;

     FindTargetRegistry &getFindRegistry() override;

     TowerMapper & getTowerMapper() override;

     EnemyMapper & getEnemyMapper() override;

     EnemyService & getEnemyService() override;

     TowerService & getTowerService() override;

     LairRepository &getLairRepository() override;

     BuildService &getBuildService () override;

     GameService & getGameService() override;

     PathCalcService & getPathService() override;

     StateService &getStateService() override;

     TowerFactoryService & getTowerFactoryService() override;

    TowerTypeRegistry & getTowerTypeRegistry() override;

    EnemyTypeRegistry & getEnemyTypeRegistry() override;

    configLoadService & getConfigLoadService() override;

    Controller & getController() override;

    // GraphicView & getGraphicView() override;





};
