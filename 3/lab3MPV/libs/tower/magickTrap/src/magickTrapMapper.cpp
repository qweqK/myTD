#include "magickTrapMapper.h"

[[nodiscard]] TowerDTO MagickTrapMapper::mapTo(const MagickTrap &from)  const {
    return {"magickTrap", from.getLevel(), from.getCost(), from.getPosition().x, from.getPosition().y, from.getAttackStrategy()->getType(), from.getRange(),  from.getLevelUpMulty(),{
        {"effect", from.getConf().behavior->getType()},
        {"duration" ,std::to_string(from.getConf().duration)},
        {"strength", std::to_string(from.getConf().strength)}
    }

    };
}

std::unique_ptr<MagickTrap> MagickTrapMapper::mapFrom(const TowerDTO & dto) const {
    auto it = dto.properties.find("effect");
    if (it == dto.properties.end()) throw std::invalid_argument("not found");
    IEffectBehavior * behavior= effectRegistry.getRaw(it->second);
    it = dto.properties.find("duration");
    if (it == dto.properties.end()) throw std::invalid_argument("not found");
    float duration = std::stof(it->second);
    it = dto.properties.find("strength");
    if (it == dto.properties.end()) throw std::invalid_argument("not found");
    float strength = std::stof(it->second);
    return  std::make_unique<MagickTrap>(dto.level, dto.cost, Point{dto.xPos, dto.yPos}, attackRegistry.getRaw(dto.attackStrategy) ,EffectConf{duration, strength, behavior}, dto.range, dto.levelMulty);
}

std::string MagickTrapMapper::getKey() const {
    return "magickTrap";
}
std::type_index MagickTrapMapper::getType() const {
    return typeid(MagickTrapMapper);
}
