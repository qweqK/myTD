#pragma once
#include "model/attackStrategy/AttackStrategy.h"

/**
 * класс реализующиф атаку для башни с магическим эффестом
 */
class MagickShootAttackStrategy : public AttackStrategy {
    public:
    /**
  *
  * @param targets возможные цели
  * @param tower башня
  */
    void attack(std::vector<IEnemy *> &targets, ITower *tower) override;
    [[nodiscard]] std::string getType() const override;///<получить имя стратегии атаки

};


