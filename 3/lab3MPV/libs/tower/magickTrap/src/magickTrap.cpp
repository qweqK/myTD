#include "magickTrap.h"

 MagickTrap::MagickTrap(int newLevel, int newCost, Point newPos, AttackStrategy * newAttackStrategy,
     EffectConf newEffect,int newRange, float levelMulty) : Trap(), MagickEffect(newEffect), DefaultTower(newLevel, newCost, newAttackStrategy, newPos, newRange, levelMulty) {}

 std::unique_ptr<ITower> MagickTrap::clone() {
     return std::make_unique<MagickTrap>(*this);
 }

void MagickTrap::levelUp() {
    range += 1*levelUpMulty;
     conf.strength *= levelUpMulty;
     cost += 50 *levelUpMulty;
}
std::string MagickTrap::getType() const {
    return "magickTrap";
}

void MagickTrap::update(float dt) {}


