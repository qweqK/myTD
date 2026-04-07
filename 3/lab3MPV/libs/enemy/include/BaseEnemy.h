#pragma once
#include <unordered_map>

#include "model/enemy/Enemy.h"
#include <unordered_map>

/**
 * класс наследник,  описывающий поведение, для базового арага
 */
class BaseEnemy : public IEnemy {
    float maxHp;///< макс хз
    float Hp;///<текущее
    float moveMulti=1.0f;///< множитель скорости
    float speed;///<скорость
    PointF pos;///<позиция
    int gold;///< количество золота
    float weak=1.0f;///< эффект слабости
    std::string name; ///< имя
    bool isDead=false;///< флаг смерти
    std::map<std::string, ActiveEffect> effectTable;///< таблицы эффектов

    public:
    BaseEnemy(float newMaxHp, float newHp, float newSpeed, int newGold, PointF newPos, std::string newName);
    void update(float dt) override;
    [[nodiscard]]std::unique_ptr<IEnemy> clone()const  override;
    void takeDamage(float damage) override;
    void applyEffect(IEffectBehavior *logic, float power, float duration) override;
    void resetEffect() override; ///< перезагрузка эффектов врагов

    void setDead() override;///< флаг смерти поставить
    void setCurHp(float h) override;
    void setMaxHp(float h) override;
    void setSpeed(float s) override;
    void multiSpeed(float m) override;
    void setPosition(PointF p) override;
    void setEnemyGold(int g) override;
    void setWeak(float w)  override;

    [[nodiscard]]bool checkDead() const override;
    [[nodiscard]] const std::string &getName() const override;
    [[nodiscard]] float getCurHp() const override;
    [[nodiscard]] float getMaxHp() const override;
    [[nodiscard]] float getSpeed()  const override;
    [[nodiscard]] PointF getPosition()const override;
    [[nodiscard]] int getEnemyGold()const override;
    [[nodiscard]] const std::map<std::string, ActiveEffect> & getEffectTab() const override; ///< получить таблицу эффектов врага



};