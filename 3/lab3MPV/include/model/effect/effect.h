#pragma once
#include <chrono>
#include <string>

class IEnemy;

/**
 * класс для описания дейстрвия эффекта
 */
class IEffectBehavior {

public:
    virtual ~IEffectBehavior() = default;

    /**
     *
     * @param target цель на которую действует эффект
     * @param power сила
     * @param dt дт
     */
    virtual void tick(IEnemy *target, float power, float dt) = 0;

   [[nodiscard]] virtual  std::string getType() const=0;///<получить имя эффекта

};


/**
 * структура описывающаяяя эффект во враге
 */
struct ActiveEffect {
    float duration;///<оставшаяся длительностью
    float strength;///<сила эффекта

    IEffectBehavior *behavior;///< указатель на повередие эффекта
    ActiveEffect() : duration(0), strength(0), behavior(nullptr) {}
};
