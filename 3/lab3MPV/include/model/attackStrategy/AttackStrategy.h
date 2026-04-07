#pragma once
#include <typeindex>

#include "model/enemy/Enemy.h"
#include "model/tower/Tower.h"
#include "model/tower/Tower.h"
#include <vector>
/**
 * осбстрактный класс для стратегии атаки
 */
class AttackStrategy {
    public:
    /**
     *
     * @param targets вектор возжвожных целей
     * @param tower башня которая атакует
     */
    virtual void attack( std::vector<IEnemy *> &targets, ITower * tower)=0;
    virtual ~AttackStrategy()=default;
    [[nodiscard]] virtual std::string getType() const=0;///<получить имя стратегии
};
