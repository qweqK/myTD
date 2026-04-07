#pragma once
#include "model/tower/Shoot.h"
#include "model/tower/Tower.h"
#include  "model/tower/Shoot.h"
#include "model/tower/Damage.h"
#include <memory>

/**
 * @brief класс, реализующий обычню башню
 */
class BaseTower : public DefaultTower, public Shoot, public DamageTower {
    public:
    explicit BaseTower( int newLevel, int newCost, Point newPos, float newDamage, float newRate, float newCooldown, int newRange, AttackStrategy* newAttack, targetFindStrategy* newShoot, float levelMulty);
    std::unique_ptr<ITower> clone() override;///< новая башня
    void update(float dt) override;
    void levelUp() override; ///< апгруйт башни
    [[nodiscard]] std::string getType() const override; ///< получение имени башни
};

