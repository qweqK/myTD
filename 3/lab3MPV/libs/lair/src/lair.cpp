#include "lair.h"
#include <iostream>
#include "model/enemy/Enemy.h"


Lair::Lair(std::deque<float> times_, std::deque<std::unique_ptr<IEnemy>>list, Point p, float time) : times(std::move(times_)), spawnList(std::move(list)), pos(p), time(time)  {}


std::unique_ptr<IEnemy> Lair::releaseEnemy(float dt) {
    time += dt;

    if (spawnList.empty()||times.empty()) {
        return nullptr;
    }
    if (time >= times.front()) {
        times.pop_front();
        std::unique_ptr<IEnemy> enemy = std::move(spawnList.front());
        spawnList.pop_front();
        return enemy;
    }
    return nullptr;
}

Point Lair::getPos() const {return pos;}
void Lair::setPos(Point p) {pos=p;}
float Lair::getTime() const {return time;}
const std::deque<float> &Lair::getTimes() const {return times;}
const std::deque<std::unique_ptr<IEnemy> > &Lair::getSpawnEnemies() const {
    return spawnList;
}



