#pragma once

#include "model/effect/effect.h"

/**
 * @brief класс, описывающий поведеничя эффекьа яда
 */
class PoisonBehavior : public IEffectBehavior {
    public:
    void tick(IEnemy *target, float power, float dt) override;
     [[nodiscard]] std::string getType() const override;
};

/**
 * @brief класс, описывающий поведение эффекта слабости
 */
class WeakBehavior : public IEffectBehavior {
    public:
    void tick(IEnemy *target, float power, float dt) override;
    [[nodiscard]] std::string  getType() const override;

};

/**
 * @brief класс описывающий поведение эффекта замедления
 */
class SlowBehavior : public IEffectBehavior {
    public:
    void tick(IEnemy *target, float power, float dt) override;
    [[nodiscard]]  std::string getType() const override;
};

