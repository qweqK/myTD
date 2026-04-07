#include "baseTower.h"
#include "model/targetFindStrategy/targetFindStrategy.h"


    BaseTower::BaseTower( const int newLevel,const int newCost,const Point newPos,const float newDamage,const float newRate,const float newCooldown,const int newRange,
        AttackStrategy *newAttack, targetFindStrategy *newShoot, float levelMulty) : DefaultTower(newLevel,newCost ,newAttack, newPos, newRange, levelMulty), Shoot(newRate, newCooldown, newShoot), DamageTower(newDamage)  {}

    std::unique_ptr<ITower> BaseTower::clone() {
        return std::make_unique<BaseTower>(*this);
    }

    void BaseTower::update(float dt) {
        setCooldown(getCooldown()-dt);
    }
    void BaseTower::levelUp() {
        damage *=levelUpMulty;
        rate /=levelUpMulty;
        rate += 1*levelUpMulty;
        cost += 50 *levelUpMulty;
    }

    std::string BaseTower::getType() const {return "baseTower";}


