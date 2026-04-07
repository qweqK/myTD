#include <complex.h>

#include "targetStrategy/include/findStrategy.h"

float distance(Point p1, PointF p2) {
    auto dx = static_cast<float>(p1.x - p2.x), dy =static_cast<float>(p1.y - p2.y);
    return dx*dx + dy*dy;
}


IEnemy *FasterFindStrategy::findTarget(Point p,std::vector<IEnemy *> &targets) const {
    if (targets.empty()) return nullptr;
    auto it = std::max_element(targets.begin(), targets.end(), [](const IEnemy* a, const IEnemy *b)
        {return a->getSpeed() < b->getSpeed();}
    );
    return *it;
}

IEnemy *WeakestFindStrategy::findTarget(Point p, std::vector<IEnemy *> &targets) const {
    if (targets.empty()) return nullptr;
    auto it  = std::min_element(targets.begin(), targets.end(), [](const IEnemy *a, const IEnemy *b)
        {return a->getCurHp() < b->getCurHp();});
    return *it;
}

IEnemy *StrangestFindStrategy::findTarget(Point p, std::vector<IEnemy *> &targets)  const{
    if (targets.empty()) return nullptr;
    auto it  = std::max_element(targets.begin(), targets.end(), [](const IEnemy *a, const IEnemy *b)
        {return a->getCurHp() < b->getCurHp();});
    return *it;
}

IEnemy *CastleNearestFindStrategy::findTarget(Point p, std::vector<IEnemy *> &targets) const {
    if (targets.empty()) return nullptr;
    auto it = std::min_element(targets.begin(), targets.end(), [this](const IEnemy *a, const IEnemy *b) {
        return (distance(castle.getLocation(), a->getPosition()) <distance(castle.getLocation(), a->getPosition()));
    });
    return *it;
}

IEnemy *NearestFindStrategy::findTarget(Point p, std::vector<IEnemy *> &targets) const {
    if (targets.empty()) return nullptr;
    auto it = std::min_element(targets.begin(), targets.end(), [&p](const IEnemy *a, const IEnemy *b) {
        return distance(p, a->getPosition()) < distance(p, b->getPosition());
    });
    return *it;
}
