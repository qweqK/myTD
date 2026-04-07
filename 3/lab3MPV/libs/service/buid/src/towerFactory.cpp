#include <iostream>

#include "towerFactoryServiceImpl.h"





void TowerFactoryImpl::create(Point pos, const std::string &towerName) const {
      std::unique_ptr<ITower> tow = towerTypeRegistry.get(towerName)->clone();
      tow->setPosition(pos);
      map.at(pos.x , pos.y).setContent(tow.get());
      towers.add(std::move(tow));


}


TowerFactoryImpl::TowerFactoryImpl(Map &map, TowerRepository & repos, TowerTypeRegistry& tReg) : map(map), towers(repos), towerTypeRegistry(tReg){}
