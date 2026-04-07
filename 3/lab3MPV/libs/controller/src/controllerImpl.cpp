#include "controllerImpl.h"


ControllerImpl::ControllerImpl(TowerTypeRegistry &towerType, TowerRepository &towerRepo, GameService &gameService, BuildService &buildService,
    Map & map, PathCalcService & pathCalcService, StateService & stateService) :
towerRepo_(towerRepo), gameService_(gameService), towerTypeRegistry_(towerType), buildService_(buildService),
map_(map), pathCalcService_(pathCalcService), stateService_(stateService){}


void ControllerImpl::updateLogic(float dt) {
    gameService_.updateGame(dt);
    gameService_.checkGameState();
    gameService_.removeTrash();
}


bool ControllerImpl::build(int x, int y, const std::string &type) {
    TerraType terra = getType(x, y);
    if (type.find("Trap")!=std::string::npos) {
        if (terra == TerraType::field) return false;
    }else if (terra == TerraType::road) return false;
    bool res = buildService_.tryBuildTower(Point{x, y}, type);
    return res;
}

bool ControllerImpl::sell(int x, int y) {
    ITower * sellTow = dynamic_cast<ITower *>(map_.at(x, y).build);
    if (sellTow!= nullptr) {
        buildService_.sellTower(sellTow);
        return true;
    }
    return false;
}

void ControllerImpl::load(const std::string &path) {
    stateService_.load(path);
    pathCalcService_.calcDistanceForMap();
}


void ControllerImpl::save(const std::string &path) {
    stateService_.save(path);
}

TerraType ControllerImpl::getType(int x, int y) {
   return  map_.at(x, y).getTerra();
}

bool ControllerImpl::levelUp(int x, int y) {
    auto tow = dynamic_cast<ITower *>(map_.at(x, y).getBuild());
    if (tow != nullptr) {
        return  buildService_.levelUp(tow);
    }
    return false;
}
