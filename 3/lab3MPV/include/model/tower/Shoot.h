#pragma once
class targetFindStrategy;

/**
 * компонент стрельбы
 */
class IShoot {
    public:
    virtual ~IShoot()=default;

    [[nodiscard]]virtual float getCooldown() const=0;
    virtual void setCooldown(float newCooldown)=0;

    [[nodiscard]]virtual float getRate() const=0;
    virtual void setRate(float newRate)=0;

    [[nodiscard]] virtual  targetFindStrategy *getTargetStrategy() const =0;
    virtual void setTargetStrategy(targetFindStrategy *newTargetStrategy) =0;

};


class Shoot : public IShoot{
    public:
    float rate;
    float cooldown;
    targetFindStrategy *targetStrategy;
    public:
    explicit Shoot(const float newRate, const float newCooldown, targetFindStrategy* newTargetStrategy) : rate(newRate), cooldown(newCooldown), targetStrategy(newTargetStrategy){}

   [[nodiscard]] float getCooldown() const override { return cooldown; }
    void setCooldown(float const newCooldown) override { cooldown = newCooldown; }


    [[nodiscard]]float getRate() const override {return rate;}
    void setRate(float const newRate) override {rate = newRate;}

    [[nodiscard]] targetFindStrategy *getTargetStrategy() const override { return targetStrategy; }
    void setTargetStrategy(targetFindStrategy *newTargetStrategy) override {targetStrategy = newTargetStrategy;};


};