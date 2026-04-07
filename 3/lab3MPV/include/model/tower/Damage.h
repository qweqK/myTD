#pragma once
/**
 * компонент дамага
 */
class IDamage {
    public:
    virtual ~IDamage() = default;
    [[nodiscard]]virtual float getDamage() const = 0;
    virtual void setDamage(float newDamage) =0;
};

class DamageTower : public IDamage {
protected:
    float damage;
    public:
    explicit DamageTower(float newDamage) : damage(newDamage) {}
    [[nodiscard]] float getDamage()  const override  { return damage; }
    void setDamage(float newDamage) override { damage = newDamage; }

};