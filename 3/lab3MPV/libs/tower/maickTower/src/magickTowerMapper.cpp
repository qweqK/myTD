#include "magickTowerMapper.h"

[[nodiscard]] TowerDTO MagickTowerMapper::mapTo(const MagickTower &from) const {
    return {"magickTower", from.getLevel(), from.getCost(), from.getPosition().x, from.getPosition().y, from.getAttackStrategy()->getType(), from.getRange(), from.getLevelUpMulty(), {
        {"range", std::to_string(from.getRange())},
        {"cooldown", std::to_string(from.getCooldown())},
        {"rate", std::to_string(from.getRate())},
        {"damage", std::to_string(from.getDamage())},
        {"shootStrategy", from.getTargetStrategy()->getType()},
        {"effect", from.getConf().behavior->getType()},
        {"duration" ,std::to_string(from.getConf().duration)},
        {"strength", std::to_string(from.getConf().strength)}

    }
    };
}


std::unique_ptr<MagickTower> MagickTowerMapper::mapFrom(const TowerDTO &dto) const {
    auto it = dto.properties.find("cooldown");
    if (it == dto.properties.end()) throw std::invalid_argument("not found: cooldown");
    float cooldown = std::stof(it->second);
    it = dto.properties.find("rate");
    if (it == dto.properties.end()) throw std::invalid_argument("not found: rate");
    int rate = std::stoi(it->second);
    it= dto.properties.find("shootStrategy");
    if (it == dto.properties.end()) throw std::invalid_argument("not found: shootStrategy");
    targetFindStrategy * shootStrategyTower = shootRegistry.getRaw(it->second);
    it = dto.properties.find("damage");
    if (it == dto.properties.end()) throw std::invalid_argument("not found: damage");
    float damage = std::stof(it->second);
    it = dto.properties.find("effect");
    if (it == dto.properties.end()) throw std::invalid_argument("not found: effect");
    IEffectBehavior * behavior= effectRegistry.getRaw(it->second);
    it = dto.properties.find("duration");
    if (it == dto.properties.end()) throw std::invalid_argument("not found: duration");
    float duration = std::stof(it->second);
    it = dto.properties.find("strength");
    if (it == dto.properties.end()) throw std::invalid_argument("not found: strength");
    float strength = std::stof(it->second);
    return  std::make_unique<MagickTower>(dto.level, dto.cost, Point{dto.xPos, dto.yPos},damage, rate, cooldown, dto.range, attackRegistry.getRaw(dto.attackStrategy), shootStrategyTower, EffectConf{duration, strength, behavior}, dto.levelMulty);

}

std::string MagickTowerMapper::getKey() const {
    return "magickTower";
}

std::type_index MagickTowerMapper::getType() const {
    return typeid(MagickTower);
}

