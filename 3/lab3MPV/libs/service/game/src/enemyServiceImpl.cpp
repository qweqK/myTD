#include "enemyServiceImpl.h"
#include  <iostream>
#include <random>

#include "castle/include/castle.h"
EnemyServiceImpl::EnemyServiceImpl(EnemyRepo &enemyRepo, Map &map, LairRepository & lairRep, Castle &castle) : enemyRepo(enemyRepo), map(map), lairRepo(lairRep), castle(castle) {}


void EnemyServiceImpl::Move(float dt) {

    for (auto &en : enemyRepo.getAllMutable()) {

        float dx = castle.getLocation().x +0.5- en->getPosition().x;
        float dy = castle.getLocation().y+0.5f - en->getPosition().y;
        if (dx*dx+dy*dy < 0.5f) {
            castle.takeDamage(en->getCurHp());
            en->setDead();
            continue;
        }
        Point curPos{static_cast<int>(en->getPosition().x), static_cast<int>(en->getPosition().y)};
        if (curPos.x < 0 || curPos.y < 0 || curPos.x > map.getCols() || curPos.y > map.getRows()) continue;
        PointF vec = map.at(curPos.x, curPos.y).flow;
        if (vec.x ==0.f && vec.y ==0.f) continue;
        en->setPosition({en->getPosition().x+vec.x*dt*en->getSpeed(), en->getPosition().y+vec.y*dt*en->getSpeed()});
    }



}


void EnemyServiceImpl::update(float dt) {
    for (auto &en : enemyRepo.getAllMutable()) {
        // en->resetEffect();
        //
        // for (auto  ef: en->getEffectTab()) {
        //     ef.second.duration-=dt;
        //     if (ef.second.duration>0) ef.second.behavior->tick(en.get(), ef.second.strength, ef.second.duration);
        //     else ef.second.strength=0;
        // }
        en->update(dt);
        if (en->getCurHp()<=0) en->setDead();

    }
}

void EnemyServiceImpl::CreateAndSpawn(float dt) {
    static std::mt19937 rng{std::random_device{}()};
    static std::uniform_real_distribution<float> dist(0.2f,0.9f);
    for (auto &lair : lairRepo.getAllMutable()) {
        PointF rp{dist(rng), dist(rng)};

        std::unique_ptr<IEnemy> enemy = lair->releaseEnemy(dt);
        if (enemy!=nullptr) {
            std::cout << "puck";
            enemy->setPosition(PointF {static_cast<float>(lair->getPos().x)+rp.x,static_cast<float> (lair->getPos().y)+rp.y});
            enemyRepo.add(std::move(enemy));
        }
    }
}









