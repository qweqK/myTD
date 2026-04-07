#pragma once
#include "model/targetFindStrategy/targetFindStrategy.h"
#include "castle/include/castle.h"

/**
 * стратегий нахождение врвгв: слабейший враг из группы
 */
class WeakestFindStrategy : public targetFindStrategy {
    public:
    IEnemy *findTarget(Point p, std::vector<IEnemy *>& targets) const  override;
    std::string getType() override {return "weakest";};
};
/**
 * стратегий нахождение врвгв: сильнейший враг из группы
 */
class StrangestFindStrategy : public targetFindStrategy {
public:
    IEnemy *findTarget(Point p, std::vector<IEnemy *> &targets) const override;
    std::string getType() override {return  "strangest";}
};
/**
 * стратегий нахождение врвгв: ближайший враг из группы
 */
class NearestFindStrategy : public targetFindStrategy {
public:
    IEnemy *findTarget(Point p, std::vector<IEnemy *>& targets) const override;
    std::string getType() override{return "nearest";};
};

/**
 * стратегий нахождение врвгв: быстрейший враг из группы
 */
class FasterFindStrategy : public targetFindStrategy {
public:
    IEnemy *findTarget(Point p, std::vector<IEnemy *> &targets) const override;
    std::string getType() override{return  "faster";};
};

/**
 * стратегий нахождение врвгв:  ближайший к амку враг из группы
 */
class CastleNearestFindStrategy : public targetFindStrategy {
    Castle &castle;
public:
    CastleNearestFindStrategy(Castle &newCastle) : castle(newCastle) {}
    IEnemy *findTarget(Point p, std::vector<IEnemy *> &targets) const override;
    std::string getType() override {return "castleNearest";}
};

// class IsStepOnTrapStrategy : public targetFindStrategy {
//     public:
//     IEnemy * findTarget(Point p, std::vector<IEnemy *> &targets) const override;
// };
