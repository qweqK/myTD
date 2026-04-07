#pragma once
#include "model/tower/Shoot.h"
#include "model/tower/Tower.h"
#include "model/tower/Magick.h"
#include "model/tower/Damage.h"
#include "model/effect/effect.h"

/**
 * @brief класс, описывающи магическую башню
 */
class MagickTower : public Shoot,public MagickEffect, public DamageTower, public  DefaultTower {
    public:
    explicit MagickTower( int newLevel, int newCost, Point newPos, float newDamage, float newRate, float newCooldown, int newRange, AttackStrategy* newAttack, targetFindStrategy* newShoot, EffectConf conf, float levelMulty);
    std::unique_ptr<ITower> clone() override; ///< клон
    void update(float dt) override;///< обновление
    void levelUp() override;///< левел ав
    std::string getType() const override;///< тип башни

};