#include "baseTowerMapper.h"

TowerDTO BaseTowerMapper::mapTo(const BaseTower &from) const {
    return {"baseTower", from.getLevel(), from.getCost(), from.getPosition().x, from.getPosition().y, from.getAttackStrategy()->getType(), from.getRange(), from.getLevelUpMulty(),{
            {"cooldown", std::to_string(from.getCooldown())},
        {"rate", std::to_string(from.getRate())},
            {"damage", std::to_string(from.getDamage())},
        {"shootStrategy", from.getTargetStrategy()->getType()}
    }
    };
}


std::unique_ptr<BaseTower> BaseTowerMapper::mapFrom(const TowerDTO &dto) const {;
    auto it = dto.properties.find("cooldown");
    if (it == dto.properties.end()) throw std::invalid_argument("not found");
    float cooldown = std::stof(it->second);
    it = dto.properties.find("rate");
    if (it == dto.properties.end()) throw std::invalid_argument("not found");
    int rate = std::stoi(it->second);
    it= dto.properties.find("shootStrategy");
    if (it == dto.properties.end()) throw std::invalid_argument("not found");
    targetFindStrategy * shootStrategyTower = shootReg.getRaw(it->second);
    it = dto.properties.find("damage");
    if (it == dto.properties.end()) throw std::invalid_argument("not found");
    float damage = std::stof(it->second);
    return std::make_unique<BaseTower>(dto.level, dto.cost, Point{dto.xPos, dto.yPos},damage, rate, cooldown, dto.range, attackRegistry.getRaw(dto.attackStrategy), shootStrategyTower, dto.levelMulty);
}

std::string BaseTowerMapper::getKey() const {
    return "baseTower";
}
std::type_index BaseTowerMapper::getType() const {
    return typeid(BaseTower);
}
