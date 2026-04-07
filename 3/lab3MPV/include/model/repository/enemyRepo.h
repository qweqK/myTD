#pragma once
#include "REPO.h"
#include "model/enemy/Enemy.h"

/**
 * склавд врагов
 */
class EnemyRepo : public  REPO<IEnemy> {
public:
    using EnemyPtr = std::unique_ptr<IEnemy>;
    [[nodiscard]]virtual  std::vector<IEnemy *>  getEnemiesInArea(PointF p,int radius)=0;///< получить врагов в заданной обалсти
    virtual  void removeDead()=0;///< очистить всех врагов с меткой дед

};


