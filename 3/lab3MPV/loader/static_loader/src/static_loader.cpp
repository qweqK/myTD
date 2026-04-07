#include "static_loader.h"

#include "attackStrategy/include/defaultAtackStrateg.h"
#include "attackStrategy/include/magickShootAtackStrateg.h"
#include "attackStrategy/include/magickTrapAtackStrategy.h"
#include "effect/include/effect.h"
#include "enemy/include/baseEnemyMapper.h"
#include "repo/registryMemory/include/attackStrategyRegistryMem.h"
#include "repo/registryMemory/include/effectStrategyRegistryMem.h"
#include "repo/registryMemory/include/enemyTypeRegistryMem.h"
#include "repo/registryMemory/include/findTargetStrategyRegistry.h"
#include "repo/repoInMemory/include/enemyRepoMem.h"
#include "repo/repoInMemory/include/lairRepoMem.h"
#include "repo/repoInMemory/include/towerRepoMem.h"
#include "service/buid/include/BuildServiceImpl.h"
#include "service/buid/include/towerFactoryServiceImpl.h"
#include "service/game/include/enemyServiceImpl.h"
#include "service/game/include/gameServiceImpl.h"
#include "service/game/include/pathServiceImpl.h"
#include "service/game/include/towerServiceImpl.h"
#include "service/load/include/configServiceImpl.h"
#include "service/load/include/stateServiceImpl.h"
#include "targetStrategy/include/findStrategy.h"
#include "tower/baseTower/include/baseTowerMapper.h"
#include "tower/magickTrap/include/magickTrapMapper.h"
#include "tower/maickTower/include/magickTowerMapper.h"


TowerRepository &StaticLoader::getTowerRepo() {
 if (!towRepo) {
  towRepo = std::make_unique<TowerRepoMem>();
 }
 return *towRepo;
}

EnemyRepo &StaticLoader::getEnemyRepo() {
 if (!enemyRepo) {
  enemyRepo = std::make_unique<EnemyRepoMem>();
    }
 return *enemyRepo;
}


AttackRegistry &StaticLoader::getAttackRegistry() {
  if (!attackRegistry) {
   attackRegistry = std::make_unique<AttackStrategyRegistryMem>();
   attackRegistry->add(std::make_unique<DefaultAttackStrategy>());
   attackRegistry->add(std::make_unique<MagickTrapAtackStrateg>(getMap()));
   attackRegistry->add(std::make_unique<MagickShootAttackStrategy>());
  }
 return *attackRegistry;
}

EffectRegistry &StaticLoader::getEffectRegistry() {
 if (!effectRegistry) {
  effectRegistry = std::make_unique<EffectBehaviorRegistryMem>();
  effectRegistry->add(std::make_unique<SlowBehavior>());
  effectRegistry->add(std::make_unique<PoisonBehavior>());
  effectRegistry->add(std::make_unique<WeakBehavior>());
 }
 return *effectRegistry;
}

FindTargetRegistry &StaticLoader::getFindRegistry() {
 if (!findRegistry) {
  findRegistry = std::make_unique<FindTargetRegistryStrategyMem>();
  findRegistry->add(std::make_unique<NearestFindStrategy>());
  findRegistry->add(std::make_unique<CastleNearestFindStrategy>(getCastle()));
  findRegistry->add(std::make_unique<FasterFindStrategy>());
  findRegistry->add(std::make_unique<WeakestFindStrategy>());
  findRegistry->add(std::make_unique<StrangestFindStrategy>());
 }
 return *findRegistry;

}

Map &StaticLoader::getMap() {
 if (!map) {
  map = std::make_unique<Map>();
 }
 return *map;
}

Castle &StaticLoader::getCastle() {
 if (!castle) {
  castle = std::make_unique<Castle>("castle", Point{-333, -333},100000, 100000, 0);
 }
 return *castle;
}

// BuildService &StaticLoader::getBuildService() {
//  if (!buildService) {
//   buildService = std::make_unique<BuildServiceImpl>(getMap(), getCastle());
//  }
//  return *buildService;
// }


LairRepository &StaticLoader::getLairRepository() {
 if (!lairRepo) {
  lairRepo = std::make_unique<LairRepoMem>();
 }
 return *lairRepo;
}


EnemyService &StaticLoader::getEnemyService() {
 if (!enemyService) {
  enemyService = std::make_unique<EnemyServiceImpl>(getEnemyRepo(), getMap(), getLairRepository(), getCastle());
 }
 return *enemyService;
}

PathCalcService &StaticLoader::getPathService() {
 if (!pathCalcService) {
  pathCalcService = std::make_unique<PathCalcServiceImpl>(getMap(), getCastle());
 }
 return *pathCalcService;
}

TowerService &StaticLoader::getTowerService() {
  if (!towerService) {
   towerService = std::make_unique<TowerServiceImpl>(getTowerRepo(), getMap(), getEnemyRepo());
  }
 return *towerService;
}

GameService &StaticLoader::getGameService() {
 if (!gameService) {
  gameService = std::make_unique<GameServiceImpl>(getEnemyService(), getTowerService(), getCastle(), getTowerRepo(), getEnemyRepo());
 }
 return *gameService;
}

EnemyMapper &StaticLoader::getEnemyMapper() {
  if (!enemyMapper) {
   enemiesSubtypeMappers.emplace_back(std::make_unique<BaseEnemySuperMapper>(getEffectRegistry()));

    auto enemyMapperLocal = std::make_unique<PolymorphicEnemyMapper>();
    for (auto & enemy : enemiesSubtypeMappers) {
      enemyMapperLocal->addSubMapper(*enemy);
    }
    enemyMapper = std::move(enemyMapperLocal);

  }
  return *enemyMapper;
}


TowerMapper &StaticLoader::getTowerMapper() {
  if (!towMapper) {
   towerSubtypeMappers.emplace_back(std::make_unique<BaseTowerSuperMapper>(getAttackRegistry(), getFindRegistry()));
   towerSubtypeMappers.emplace_back(std::make_unique<MagickTowerSuperMapper>(getAttackRegistry(), getEffectRegistry(), getFindRegistry()));
   towerSubtypeMappers.emplace_back(std::make_unique<MagickTrapSupperMapper>( getEffectRegistry(), getAttackRegistry()));

   auto towerMapperLocal = std::make_unique<PolymorphicTowerMapper>();
   for (auto & tow : towerSubtypeMappers) {
    towerMapperLocal->addSubMapper(*tow);
   }
   towMapper = std::move(towerMapperLocal);
  }
 return *towMapper;

}

TowerTypeRegistry &StaticLoader::getTowerTypeRegistry() {
 if (!towerTypeRegistry) {
  towerTypeRegistry = std::make_unique<TowerTypeRegistryImpl>();
 }
 return *towerTypeRegistry;
}


TowerFactoryService &StaticLoader::getTowerFactoryService(){
    if (!towFactoryService) {
        towFactoryService = std::make_unique<TowerFactoryImpl>(getMap(), getTowerRepo(), getTowerTypeRegistry());
    }
    return *towFactoryService;
}

BuildService &StaticLoader::getBuildService() {
  if (!buildService) {
   buildService = std::make_unique<BuildServiceImpl>(getTowerRepo(), getTowerFactoryService(),  getMap(), getCastle(), getTowerTypeRegistry());
  }
 return *buildService;
}

StateService &StaticLoader::getStateService() {
  if (!stateServiceLoader) {
   stateServiceLoader = std::make_unique<StateServiceImpl>(getTowerRepo(), getMap(), getEnemyRepo(), getCastle(), getLairRepository(), getEnemyMapper(), getEnemyTypeRegistry(), getTowerMapper());
  }
 return *stateServiceLoader;
}

EnemyTypeRegistry &StaticLoader::getEnemyTypeRegistry() {
 if (!enemyTypeRegistry) {
  enemyTypeRegistry = std::make_unique<EnemyTypeRegistryMem>();

 }
 return *enemyTypeRegistry;
}


configLoadService &StaticLoader::getConfigLoadService() {
 if (!cconfigLoadService) {
  cconfigLoadService = std::make_unique<configLoadServiceImpl>(getEnemyTypeRegistry(), getTowerMapper(), getEnemyMapper(), getTowerTypeRegistry());
 }
 return *cconfigLoadService;
}

// GraphicView &StaticLoader::getGraphicView() {
//  if (!view) {
//   view = std::unique_ptr<GraphicView>();
//  }
//  return *view;
// }

Controller & StaticLoader::getController() {
 if (!controller) {
  controller = std::make_unique<ControllerImpl>(getTowerTypeRegistry(), getTowerRepo(), getGameService(),getBuildService(), getMap(), getPathService(), getStateService());
 }
 return *controller;
}

