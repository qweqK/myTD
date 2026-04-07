#include "attackStrategy/include/magickShootAtackStrateg.h"

#include "tower/maickTower/include/magickTower.h"
#include "model/targetFindStrategy/targetFindStrategy.h"
#include  <iostream>

void MagickShootAttackStrategy::attack(std::vector<IEnemy *> &targets, ITower *tower) {
    auto ptr = dynamic_cast<MagickTower*>(tower);
    if (ptr!=nullptr && ptr->getCooldown()<=0) {
        IEnemy *target = ptr->getTargetStrategy()->findTarget(ptr->getPosition(), targets);
        if(target!=nullptr) {
            target->takeDamage(ptr->getDamage());
            ptr->setCooldown(ptr->getRate());
            std::cout << "bac"<< std::endl;
            if (target->getCurHp()<=0) {
                target->setDead();
                return;
            }

            target->applyEffect(ptr->getConf().behavior, ptr->getConf().strength, ptr->getConf().duration);

        }
    }
}

std::string MagickShootAttackStrategy::getType() const {
    return "magickShootAttack";
}

