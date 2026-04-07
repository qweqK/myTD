#include "attackStrategy/include/defaultAtackStrateg.h"
#include "targetStrategy/include/findStrategy.h"
#include "tower/baseTower/include/baseTower.h"
#include "model/tower/Tower.h"
#include "model/tower/Shoot.h"
#include "model/tower/Damage.h"
#include "iostream"

void DefaultAttackStrategy::attack( std::vector<IEnemy *> &targets, ITower *tower) {
    auto baseTower =  dynamic_cast<BaseTower *>( tower);
    if (baseTower!=nullptr && baseTower->getCooldown()<=0) {
        IEnemy * target= baseTower->getTargetStrategy()->findTarget(tower->getPosition(),targets);
        if(target!=nullptr) {
            target->takeDamage(baseTower->getDamage());
            baseTower->setCooldown(baseTower->getRate());
            std::cout << "bac"<< std::endl;
            if (target->getCurHp()<=0) target->setDead();
         }
    }
}

std::string DefaultAttackStrategy::getType() const {
    return "defaultAttack";
}
