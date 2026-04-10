#pragma once
#include "model/enemy/Enemy.h"
#include "model/tower/Tower.h"
/**
* интерфейс, для описания стратегии поиска цели
*/
class targetFindStrategy {
   public:
   /**
    *
    * @param p точка относительно которой ищем
    * @param targets кандидаты для стрельбы
    * @return конкретный враг
    */
   virtual IEnemy* findTarget(Point p, std::vector<IEnemy *> &targets) const=0;

   virtual std::string getType() =0;///< получить тип стратегии
   virtual ~targetFindStrategy() = default;

};
