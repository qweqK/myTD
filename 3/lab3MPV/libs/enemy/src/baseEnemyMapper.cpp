
#include "baseEnemyMapper.h"

EnemyDto BaseEnemyMapper::mapTo(const BaseEnemy &from) const {
    EnemyDto enemy{from.getName(), "base", from.getCurHp(),
                from.getMaxHp(), from.getSpeed(), from.getPosition().x, from.getPosition().y, from.getEnemyGold()};

    for ( auto &ef: from.getEffectTab()) {
        enemy.effectTable[ef.first]= std::make_pair(ef.second.duration, ef.second.strength);
    }
    return enemy;}

std::unique_ptr<BaseEnemy> BaseEnemyMapper::mapFrom(const EnemyDto &dto) const {
    std::unique_ptr<BaseEnemy> to = std::make_unique<BaseEnemy>(dto.maxHp, dto.curHp, dto.speed, dto.gold, PointF{dto.posX, dto.posY}, dto.name);
    for (auto &ef: dto.effectTable ) {
        to->applyEffect(effectRegistry.getRaw(ef.first), ef.second.first, ef.second.second);
    }
    return to;}

std::string BaseEnemyMapper::getKey() const {
    return "base";
}

std::type_index BaseEnemyMapper::getType() const {
    return typeid(BaseEnemy);
}




