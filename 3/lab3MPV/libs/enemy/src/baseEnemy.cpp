#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(float newMaxHp, float newHp, float newSpeed, int newGold,
     PointF newPos, std::string newName) : speed(newSpeed), gold(newGold), maxHp(newMaxHp), Hp(newHp),  pos(newPos), name(std::move(newName)) {}

void BaseEnemy::setCurHp(float h) {Hp=  h;  }
void BaseEnemy::setMaxHp(float h) {maxHp = h;}
void BaseEnemy::setSpeed(float s) {speed= s;}
void BaseEnemy::multiSpeed(float m) {moveMulti*=m;}
void BaseEnemy::setPosition( PointF p) {pos= p;}
void BaseEnemy::setEnemyGold(int g) { gold = g;}
//void BaseEnemy::setMaxSpeeed(float s) { moveMulti = s;}
void BaseEnemy::setDead() { isDead = true;}
void BaseEnemy::setWeak(float w)  {weak *=w;}


const std::string &BaseEnemy::getName() const { return name;}
float BaseEnemy::getCurHp() const { return Hp;}
float BaseEnemy::getSpeed() const { return speed/moveMulti;}

int BaseEnemy::getEnemyGold()const  { return gold;}
PointF BaseEnemy::getPosition()const  { return pos;}
float BaseEnemy::getMaxHp()const  { return maxHp;}
bool BaseEnemy::checkDead() const {  return isDead;}


const std::map<std::string, ActiveEffect> &BaseEnemy::getEffectTab() const { return effectTable;}



void BaseEnemy::takeDamage(float damage) {Hp-= damage*weak;}
std::unique_ptr<IEnemy> BaseEnemy::clone() const {return std::make_unique<BaseEnemy>(*this);}

void BaseEnemy::applyEffect(IEffectBehavior *logic, float power, float duration) {
    auto &ActEff= effectTable[logic->getType()];
    ActEff.behavior=logic;
    ActEff.duration+=duration;
    ActEff.strength+=power;
}

void BaseEnemy::resetEffect() {
    moveMulti = 1.0f;
    weak = 1.0f;
}

void BaseEnemy::update(float dt) {
    resetEffect();
    for (auto & ef: effectTable) {
            ef.second.duration -= dt;
            if (ef.second.duration>=0) {
                ef.second.behavior->tick(this,ef.second.strength ,dt);
            }
            else {
                ef.second.duration=0;
                ef.second.strength=0.0f;
            }
        }
}













