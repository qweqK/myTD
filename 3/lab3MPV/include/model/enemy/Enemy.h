#pragma once
#include "model/effect/effect.h"
#include "model/point/point.h"
#include <string>
#include <map>

class IEffectBehavior;
struct ActiveEffect;

/**
 * @обстрактный описатель врага
 *
 */
class IEnemy {
    public:
    virtual ~IEnemy()= default;
    [[nodiscard]] virtual const std::string &getName() const=0;///< получить имя
    [[nodiscard]] virtual float getCurHp() const=0;///< получить текущ хп
    [[nodiscard]] virtual float getMaxHp() const=0;///< получть макс хп
    [[nodiscard]] virtual float getSpeed() const=0;///< получть скорость
    [[nodiscard]] virtual PointF getPosition() const=0;///< получить корды
    [[nodiscard]] virtual int getEnemyGold() const=0;///< получить кол во звлота сколько у него
   // [[nodiscard]] virtual  float getMaxSpeed() const=0;
    [[nodiscard]] virtual const std::map<std::string, ActiveEffect> & getEffectTab() const=0; ///< получить таблицу эффектов
    //[[nodiscard]] virtual float getWeak() const =0;
    [[nodiscard]] virtual bool checkDead() const =0;///< проверка на сметрть

    virtual void resetEffect()=0;///< сбросить эмножителей ффекта в начале хода


    virtual void setDead()=0;
    virtual void setCurHp(float h)=0;
    virtual void setMaxHp(float h)=0;
    virtual void setSpeed(float s)=0;
    virtual void setPosition(PointF p)=0;
    virtual void setEnemyGold(int g)=0;
    virtual void multiSpeed(float m)=0;
    //virtual void setMaxSpeeed(float s) = 0;
    virtual void setWeak(float w) =0;

    [[nodiscard]] virtual std::unique_ptr<IEnemy> clone() const=0;///< копия врага

    virtual void takeDamage(float damage)=0;///< получить урон


    virtual void applyEffect(IEffectBehavior *logic, float power, float duration)=0;///< принять эффект откудо та

    virtual void update(float dt)=0; ///< оновление логики врага

};
