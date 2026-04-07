#pragma once
#include "model/buildings/Build.h"
#include "model/point/point.h"
#include <string>
#include <memory>


class AttackStrategy;

/**
 * компонент башни
 */
class ITower : public IBuild {
    public:
    [[nodiscard]]virtual int getLevel() const=0;
    virtual void setLevel(int newLevel)=0;

    [[nodiscard]]virtual int getCost() const =0;
    virtual void setCost(int newCost)=0;

    [[nodiscard]]virtual Point getPosition()const=0;
    virtual void setPosition(Point point)=0;

    [[nodiscard]]virtual int getRange() const=0;
    virtual void setRange(int newRange)=0;

    virtual  void update(float dt)=0;

    virtual std::unique_ptr<ITower> clone()=0;

    virtual  void levelUp()=0;

    [[nodiscard]]virtual std::string getType()const=0;

    virtual void setDead()=0;
    [[nodiscard]] virtual bool checkDead() const =0;

    virtual  void setLevelUpMulty(float levelMulty)=0;
    [[nodiscard]] virtual  float getLevelUpMulty() const =0;

    [[nodiscard]]  virtual AttackStrategy * getAttackStrategy() const=0;


};

class DefaultTower : public ITower {
    protected:
    int level;
    int cost;
    Point position;
    AttackStrategy *attackStrategy;
    int range;
    float levelUpMulty;
    bool isDead=false;

    explicit DefaultTower(int const level, int const cost, AttackStrategy *attackStrategy,const Point pos, int newRange, float levelMulty) : level(level), cost(cost),  position(pos), attackStrategy(attackStrategy), range(newRange), levelUpMulty(levelMulty) {}
    public:
    [[nodiscard]]int getLevel() const override {return level;}
    void setLevel(const int newLevel) override {level=newLevel;}

    void setCost(const int newCost) override {cost=newCost;}
    [[nodiscard]]int getCost()const override {return cost;}

    [[nodiscard]]Point getPosition()const override {return position;}
    void setPosition(const Point point) override {position=point;}

    void setDead() override {isDead = true;}
    [[nodiscard]]bool checkDead()const override {return isDead;}

    void setAttackStrategy(AttackStrategy* newAttackStrategy) {attackStrategy=newAttackStrategy;}
   [[nodiscard]] AttackStrategy * getAttackStrategy() const override { return attackStrategy;}

   [[nodiscard]] int getRange() const override{return range;}
    void setRange(int newRange) override {range=newRange;}


    [[nodiscard]]float getLevelUpMulty() const override {return levelUpMulty;}
    void setLevelUpMulty(float levelMulty) override{levelUpMulty=levelMulty;}

};

