#include "effect.h"
#include "model/enemy/Enemy.h"

void PoisonBehavior::tick(IEnemy *target, float power, float dt) {
    target->takeDamage(dt*power);
}

std::string PoisonBehavior::getType() const {
    return "Poison";
}

void WeakBehavior::tick(IEnemy *target, float power, float dt) {
    target->setWeak(power);
}

std::string WeakBehavior::getType() const {
    return "Weak";
}

void SlowBehavior::tick(IEnemy *target, float power, float dt) {
    target->multiSpeed(power);
}

std::string SlowBehavior::getType() const {
    return "Slow";
}








