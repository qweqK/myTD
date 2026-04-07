#pragma once
#include "model/attackStrategy/AttackStrategy.h"

/**
 * класс наследник, реализующий стратегии атакидля для обычной башни
 */
class DefaultAttackStrategy : public AttackStrategy {
public:
    /**
     *
     * @param targets возможные цели
     * @param tower башня
     */
    void attack( std::vector<IEnemy *> &targets, ITower *tower) override;
    [[nodiscard]] std::string getType() const override; ///< получить имя стратегии аттаки

};