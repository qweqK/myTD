#pragma once
#include "model/tower/Magick.h"
#include "model/tower/Tower.h"
#include "model/tower/Trap.h"

/**
 * @brief описатель магической башни
 */
class MagickTrap : public Trap, public MagickEffect, public DefaultTower {
    public:
    MagickTrap(int newLevel, int newCost, Point newPos, AttackStrategy * newAttackStrategy, EffectConf newEffect, int newRange, float levelMulty);
    std::unique_ptr<ITower> clone() override;///< клонирование башни
    void levelUp() override; ///< лквел ап
    void update(float dt) override; ///< аптдейт
    std::string getType() const override; ///< получить тип
};