#include "magickTower.h"

#include "tower/baseTower/include/baseTower.h"

MagickTower::MagickTower(int newLevel, int newCost, Point newPos, float newDamage,
                         float newRate, float newCooldown, int newRange,
                         AttackStrategy *newAttack, targetFindStrategy *newShoot, EffectConf conf, float levelMulty) : Shoot(newRate,newCooldown, newShoot),
                         MagickEffect(conf) ,DamageTower(newDamage), DefaultTower(newLevel, newCost, newAttack, newPos, newRange, levelMulty){}

std::unique_ptr<ITower> MagickTower::clone () {return std::make_unique<MagickTower>(*this);}
void MagickTower::update(float dt) {
    setCooldown(getCooldown()-dt);
}
void MagickTower::levelUp() {
    damage *=levelUpMulty;
    rate /=levelUpMulty;
    rate += 1*levelUpMulty;
    conf.strength += 0.5 * levelUpMulty;
    cost += 50 *levelUpMulty;
}


std::string MagickTower::getType() const {
    return "magickTower";
}


