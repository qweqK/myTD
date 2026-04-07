#pragma once
#include "service/game/include/pathServiceImpl.h"
#include "controller/Controller.h"
#include "model/repository/towerTypeRegistry.h"
#include "model/repository/enemyRepo.h"
#include "model/repository/towerRepo.h"
#include "cell/include/cell.h"
#include "map/include/map.h"
#include "model/service/build/BuildService.h"
#include "model/service/game/GameService.h"
#include "model/service/load/StateService.h"

class ControllerImpl : public Controller {
    TowerTypeRegistry &towerTypeRegistry_;
    TowerRepository & towerRepo_;
    GameService & gameService_;
    BuildService & buildService_;
    Map & map_;
    PathCalcService & pathCalcService_;
    StateService & stateService_;


    public:
    ControllerImpl(TowerTypeRegistry & towerType, TowerRepository & towerRepo, GameService & gameService, BuildService & buildService, Map & map, PathCalcService & pathCalcService, StateService & stateService);
    void updateLogic(float dt) override;
    bool build(int x, int y,const std::string &type) override;
    bool sell(int x, int y) override;
    TerraType getType(int x, int y) override;
    void save(const std::string &path) override;
    void load(const std::string &path) override;
    bool levelUp(int x, int y) override;



};
