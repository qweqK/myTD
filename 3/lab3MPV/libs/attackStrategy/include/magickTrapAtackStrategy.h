#pragma once
#include "map/include/map.h"
#include "model/attackStrategy/AttackStrategy.h"

/**
 *
 * наследник класс, реализующий логику атаки ловушки
 */
class MagickTrapAtackStrateg : public AttackStrategy {
    Map & map;
public:
    MagickTrapAtackStrateg(Map & map) : map(map) {}

    /**
     *
     * @param targets возможные цели
     * @param tower башня
     */
    void attack(std::vector<IEnemy *> &targets, ITower *tower) override;
    [[nodiscard]] std::string getType() const override;///<имя аттаки

};