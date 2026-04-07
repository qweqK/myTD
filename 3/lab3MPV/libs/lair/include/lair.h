#pragma once
#include <deque>
#include "dto/EnemyDto.h"
#include "model/enemy/Enemy.h"
#include "model/buildings/Build.h"

/**
 * @brief класс, описывающий, поведение логова
 */
class Lair : public  IBuild {
    std::deque<std::unique_ptr<IEnemy>> spawnList;///<очередь врагов
    std::deque<float> times;///< очередь времен
    float time;///< время, от которого считается, когда выпутить врага
    Point pos;///< позиция логова
public:
    /**
     * консруктор
     * @param times_ временм
     * @param enemiesList враги
     * @param p позиыия
     * @param time время
     */
    Lair(std::deque<float> times_, std::deque<std::unique_ptr<IEnemy>> enemiesList, Point p, float time);

    /**
     * @brief в случае того, если время подошло, возарвщает вравг из очореди
     * @param dt дельтованное время
     * @return юник птр на врага
     */
    std::unique_ptr<IEnemy> releaseEnemy(float dt);

    [[nodiscard ]]Point getPos() const;
    void setPos(Point p);
    [[nodiscard]]const std::deque<float> & getTimes() const;
    [[nodiscard]]float getTime() const;
    [[nodiscard]]const std::deque<std::unique_ptr<IEnemy>> &getSpawnEnemies() const;


};