#include <atomic>
#include <iostream>

#include "../loader/static_loader/include/static_loader.h"
#include "attackStrategy/include/defaultAtackStrateg.h"
#include "attackStrategy/include/magickTrapAtackStrategy.h"
#include "attackStrategy/include/magickShootAtackStrateg.h"
#include "catch2/catch_all.hpp"
#include "enemy/include/BaseEnemy.h"
#include "tower/baseTower/include/baseTower.h"

TEST_CASE("loadFromFile") {
    SECTION("Config") {
        std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
        EnemyRepo & repo = loader->getEnemyRepo();
        loader->getConfigLoadService().load("config/config.yaml");
        REQUIRE(loader->getTowerTypeRegistry().getRaw("baseTower")!=nullptr);
        REQUIRE(loader->getTowerTypeRegistry().getRaw("magickTower")!=nullptr);
        REQUIRE(loader->getTowerTypeRegistry().getRaw("magickTrap")!=nullptr);
        REQUIRE(loader->getEnemyTypeRegistry().getRaw("orc")!=nullptr);
        REQUIRE(loader->getEnemyTypeRegistry().getRaw("troll")!=nullptr);
        REQUIRE(loader->getEnemyTypeRegistry().getRaw("goblin")!=nullptr);

    }
    SECTION("state") {
        std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
        EnemyRepo & repo = loader->getEnemyRepo();
        loader->getConfigLoadService().load("config/config.yaml");
        loader->getStateService().load("save/save2.json");
        REQUIRE(!loader->getEnemyRepo().getAll().empty());
        REQUIRE(!loader->getTowerRepo().getAll().empty());
        REQUIRE(!loader->getLairRepository().getAll().empty());
        REQUIRE(loader->getMap().getSize()==150);
        REQUIRE(loader->getCastle().getName()=="arturvelikiy");
    }
    SECTION("save") {
        std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
        EnemyRepo & repo = loader->getEnemyRepo();
        loader->getConfigLoadService().load("config/config.yaml");
        loader->getStateService().load("save/save2.json");
        loader->getStateService().save("save/save3.json");
        loader->getStateService().load("save/save3.json");
        REQUIRE(loader->getCastle().getName()=="arturvelikiy");
    }
}


TEST_CASE("AttackStrategy") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/testDefaultAttack.json");
    std::unique_ptr<IEnemy> en1 = loader->getEnemyTypeRegistry().get("orc")->clone();
    std::vector<IEnemy *> vec;
    vec.push_back(en1.get());
    SECTION("defaultAttack") {
        std::unique_ptr<ITower> tower = loader->getTowerTypeRegistry().get("baseTower")->clone();
        tower->setPosition({5, 6});
        AttackStrategy * attackStrat = loader->getAttackRegistry().getRaw("defaultAttack");
        REQUIRE(attackStrat->getType()=="defaultAttack");
        attackStrat->attack(vec, tower.get());
        REQUIRE(vec.at(0)->getCurHp()==60);

    }
    SECTION("magickAttack") {
        std::unique_ptr<ITower> tower = loader->getTowerTypeRegistry().get("magickTower")->clone();
        tower->setPosition({5, 6});
        AttackStrategy * attackStrat = loader->getAttackRegistry().getRaw("magickShootAttack");
        REQUIRE(attackStrat->getType()=="magickShootAttack");
        attackStrat->attack(vec, tower.get());
        REQUIRE(vec.at(0)->getCurHp()==105);
        REQUIRE(vec.at(0)->getEffectTab().at("Slow").behavior->getType()=="Slow");
    }
    SECTION("magickTrap") {
        std::unique_ptr<ITower> tower = loader->getTowerTypeRegistry().get("magickTrap")->clone();
        vec.at(0)->setPosition({5,6});
        tower->setPosition({5, 6});
        AttackStrategy * attackStrat = loader->getAttackRegistry().getRaw("magickTrapAttack");
        REQUIRE(attackStrat->getType()=="magickTrapAttack");
        attackStrat->attack(vec, tower.get());
        REQUIRE(vec.at(0)->getEffectTab().at("Slow").behavior->getType()=="Slow");
    }
}

TEST_CASE("FindTargetStrategy") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/testDefaultAttack.json");
    std::unique_ptr<IEnemy> en1 = loader->getEnemyTypeRegistry().get("orc")->clone();
    std::unique_ptr<IEnemy> en2 = loader->getEnemyTypeRegistry().get("orc")->clone();
    en1->setPosition({2, 2});
    en2->setPosition({3, 3});
    en2->setCurHp(69);
    en2->setSpeed(100);
    loader->getCastle().setLocation({1, 1});
    AttackStrategy *attack = loader->getAttackRegistry().getRaw("defaultAttack");
    std::vector<IEnemy *> vec;
    vec.push_back(en1.get());
    vec.push_back(en2.get());
    SECTION("Nearest") {
        targetFindStrategy * strat = loader->getFindRegistry().getRaw("nearest");
        IEnemy* res = strat->findTarget({5,6}, vec);
        REQUIRE(res->getCurHp()==69);
        REQUIRE(strat->getType() == "nearest");
    }
    SECTION("CastleNearest") {
        targetFindStrategy * strat = loader->getFindRegistry().getRaw("castleNearest");
        IEnemy* res = strat->findTarget({5,6}, vec);
        REQUIRE(res->getCurHp()==120);
    }
    SECTION("Weakest") {
        targetFindStrategy * strat = loader->getFindRegistry().getRaw("weakest");
        IEnemy * res = strat->findTarget({5,6}, vec);
        REQUIRE(res->getCurHp()==69);
    }
    SECTION("faster") {
        targetFindStrategy * strat = loader->getFindRegistry().getRaw("faster");
        IEnemy * res = strat->findTarget({5,6}, vec);
        REQUIRE(res->getCurHp()==69);
    }
    SECTION("strangest") {
        targetFindStrategy * strat = loader->getFindRegistry().getRaw("strangest");
        IEnemy * res = strat->findTarget({5,6}, vec);
        REQUIRE(res->getCurHp()==120);
    }
}
TEST_CASE("effect") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    auto& repo = loader->getEnemyRepo();
    loader->getStateService().loadEnemy("save/enemyEf.json");
    SECTION("effect") {
        IEnemy * en = repo.getAll().at(0).get();
        en->update(1);
        en->takeDamage(1);
        REQUIRE(en->getCurHp()==30);
        REQUIRE(en->getSpeed()==0.4f);
    }
}


TEST_CASE("lair") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().loadLairs("state/lairs.json");
    Lair * lair = loader->getLairRepository().getAll().at(0).get();
    auto en  = lair->releaseEnemy(1.f);
    REQUIRE(en->getCurHp()==120);
    auto en2 = lair->releaseEnemy(1.f);
    REQUIRE(en2==nullptr);
    lair->releaseEnemy(19);
    auto en3 = lair->releaseEnemy(1.f);
    REQUIRE(en3==nullptr);
}


TEST_CASE("move/map") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/save2.json");
    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    Map & map = loader->getMap();
    REQUIRE(map.at(1, 0).getPriority()==18);
    SECTION("move") {
        auto enPos1 = repo.getAll().at(0).get()->getPosition();
        loader->getEnemyService().Move(1);
        auto enPos2 = repo.getAll().at(0).get()->getPosition();
        REQUIRE((enPos1.x+enPos1.y) < (enPos2.x+enPos2.y));
        repo.getAll().at(0).get()->setPosition({11.5,8});
        loader->getEnemyService().Move(1);
        REQUIRE(repo.getAll().at(0).get()->checkDead()==true);

    }
}
TEST_CASE("enemyServ") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/saveEnqw.json");
    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    SECTION("CreateAndSpawn") {
        loader->getEnemyService().CreateAndSpawn(1.1);
        REQUIRE(repo.getAll().size()==2);
    }
    SECTION("update") {
        loader->getEnemyService().update(1);
        auto en = repo.getAll().at(0).get();
        REQUIRE(en->getCurHp()==30);
        loader->getEnemyService().update(1);
        auto en2 = repo.getAll().at(0).get();
        REQUIRE(en2->checkDead()==true);
    }
}
TEST_CASE("towerSerevice") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/saveTow.json");
    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    SECTION("update") {
        loader->getTowerService().updateTower(1);
        auto en = repo.getAll().at(0).get();
        REQUIRE(en->getCurHp()==96);
    }

}

TEST_CASE("game") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/saveTow.json");
    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    loader->getGameService().updateGame(1);
    repo.getAll().at(0).get()->setDead();
    loader->getGameService().removeTrash();
    REQUIRE(repo.getAll().empty());
    REQUIRE(loader->getGameService().checkGameState()==Game::PROCESS);
}

TEST_CASE("build") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/saveTow.json");
    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    loader->getBuildService().tryBuildTower({1, 1}, "baseTower");
    REQUIRE(loader->getTowerRepo().getAll().size()==2);
    loader->getBuildService().tryBuildTower({1, 1}, "baseTower");
    REQUIRE(loader->getTowerRepo().getAll().size()==2);
    loader->getBuildService().levelUp(dynamic_cast<ITower *>(loader->getMap().at(1,1).build));

    loader->getBuildService().sellTower(dynamic_cast<ITower *>(loader->getMap().at(1,1).build));
    loader->getGameService().removeTrash();
    REQUIRE(loader->getTowerRepo().getAll().size()==1);
    loader->getBuildService().tryBuildTower({1, 2}, "magickTower");
    loader->getBuildService().tryBuildTower({1, 3}, "magickTrap");
    loader->getBuildService().levelUp(dynamic_cast<ITower *>(loader->getMap().at(1,2).build));
    loader->getBuildService().levelUp(dynamic_cast<ITower *>(loader->getMap().at(1,3).getBuild()));



}


TEST_CASE("different trash") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getStateService().load("save/saveTow.json");
    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    SECTION("enemy") {
        repo.getAll().at(0).get()->setMaxHp(30);
        repo.getAll().at(0).get()->setEnemyGold(30);
        REQUIRE(repo.getAll().at(0).get()->getMaxHp()==30);
        REQUIRE(repo.getAll().at(0)->getEnemyGold()==30);
    }
    SECTION("repoReg") {
        REQUIRE(loader->getAttackRegistry().get("defaultAttack")->getType()=="defaultAttack");
        REQUIRE(loader->getEffectRegistry().get("Slow")->getType()=="Slow");
        REQUIRE(loader->getFindRegistry().get("nearest")->getType()=="nearest");
        loader->getAttackRegistry().clear();
        loader->getEffectRegistry().clear();
        loader->getFindRegistry().clear();
        loader->getTowerTypeRegistry().clear();
        REQUIRE_THROWS(loader->getAttackRegistry().get("defaultAttack")->getType());
        REQUIRE_THROWS(loader->getEffectRegistry().get("Slow")->getType());
        REQUIRE_THROWS(loader->getFindRegistry().get("nearest")->getType());
        REQUIRE_THROWS(loader->getTowerTypeRegistry().get("defaultTower")->getType());
        REQUIRE(loader->getTowerRepo().getAllMutable().size()==1);
        }
        SECTION("load") {
        loader->getStateService().loadCastle("state/castle.json");
        REQUIRE(loader->getCastle().getName()=="arturvelikiy");
        loader->getStateService().loadMap("state/map.json");
        REQUIRE(loader->getMap().getSize()==150);
        loader->getStateService().loadTower("state/towers.json");
        REQUIRE(loader->getTowerRepo().getAll().size()==2);

    }


}

TEST_CASE("Controller") {
    std::unique_ptr<StaticLoader> loader = std::make_unique<StaticLoader>();
    EnemyRepo & repo = loader->getEnemyRepo();
    loader->getConfigLoadService().load("config/config.yaml");
    loader->getController().load("save/saveTow.json");
    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    loader->getController().build(1, 2, "baseTower");
    loader->getController().save("save/saveq.json");
    loader->getController().levelUp(1, 2);
    loader->getController().sell(1, 2);
    loader->getController().updateLogic(1);
    REQUIRE(loader->getController().getType(1, 0)==TerraType::road);
}



