#include  "BuildServiceImpl.h"
#include "towerFactoryServiceImpl.h"

BuildServiceImpl::BuildServiceImpl(TowerRepository &towerRepo, TowerFactoryService &towerFactory, Map &nMap, Castle &castle, TowerTypeRegistry &towerTypeReg) :towerRepo(towerRepo), towerFactory(towerFactory), map(nMap), castle(castle), towerTypeRegistry(towerTypeReg) {}

void BuildServiceImpl::sellTower(ITower *tower) {
    castle.setGold(castle.getGold()+tower->getCost());
    tower->setDead();
    map.at(tower->getPosition().x, tower->getPosition().y).deleteContent();
}

bool BuildServiceImpl::tryBuildTower(Point pos,const std::string & name) {
    if (castle.getGold()< towerTypeRegistry.getRaw(name)->getCost()) return false;
    if (map.at(pos.x, pos.y).isContent()!=false||map.at(pos.x, pos.y).type == TerraType::forest) return false;
    towerFactory.create(pos, name);
    castle.setGold(castle.getGold()-towerTypeRegistry.getRaw(name)->getCost());
    return true;
}

bool BuildServiceImpl::levelUp(ITower *tower) {
    int cost = tower->getCost()/3;
    if (castle.getGold()<cost) return false;
    if (tower->getLevel()>=3 ) return false;
    tower->levelUp();
    tower->setLevel(tower->getLevel()+1);
    castle.setGold(castle.getGold()-cost);
    return true;
}

