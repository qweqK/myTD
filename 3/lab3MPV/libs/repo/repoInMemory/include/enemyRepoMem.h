#pragma once
#include "model/repository/enemyRepo.h"

/**
 * @репозиторий врагов
 */
class EnemyRepoMem : public EnemyRepo {
public:
   /**
    *
    * @param object добавить врага
    */
   void add(EnemyPtr object) override;

   /**
    * @brief получить всех врагов
    * @return враги
    */
   [[nodiscard]]const std::vector<EnemyPtr>& getAll() const override;

   /**
    *
    * @return получить всех аргов, можно изменять
    */
   [[nodiscard]]std::vector<EnemyPtr>& getAllMutable() override;

   /**
    *
    * @param p точка от которой ищем в радиусе
    * @param radius радиус
    * @return все враги в этом радиусе
    */
   std::vector<IEnemy *>  getEnemiesInArea(PointF p, int radius) override;
   void removeDead() override; ///< удалить сдохших
   void clear() override; ///< очистить



private:

   std::vector<EnemyPtr> data;


};
