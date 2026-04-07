#include "attackStrategy/include/magickTrapAtackStrategy.h"

#include "tower/magickTrap/include/magickTrap.h"

void MagickTrapAtackStrateg::attack(std::vector<IEnemy *> &targets, ITower *tower) {
    MagickTrap *ptr= dynamic_cast<MagickTrap *>(tower);
    if (ptr != nullptr) {
         for (auto i : targets) {
             if (std::abs(i->getPosition().x- ptr->getPosition().x) <0.5 && std::abs(i->getPosition().y - ptr->getPosition().y) <0.5) {
                 for (auto j : targets) {
                     j->applyEffect(ptr->getConf().behavior, ptr->getConf().strength, ptr->getConf().duration);
                 }
                 ptr->setDead();
                 map.at(ptr->getPosition().x, ptr->getPosition().y).deleteContent();
                 return;
             }
         }
    }
}

std::string MagickTrapAtackStrateg::getType() const {
    return "magickTrapAttack";
}
