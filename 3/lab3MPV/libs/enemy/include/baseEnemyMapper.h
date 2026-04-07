#pragma once
#include "mapper/enemyMapper.h"
#include "BaseEnemy.h"
#include "model/repository/effectRegistry.h"
class BaseEnemyMapper : public ConcreteEnemyMapper<BaseEnemy> {
    EffectRegistry &effectRegistry;
    public:
   explicit  BaseEnemyMapper(EffectRegistry &effectRegistry) : effectRegistry(effectRegistry) {}
    [[nodiscard]] EnemyDto mapTo(const BaseEnemy &) const override;
    [[nodiscard]] std::unique_ptr<BaseEnemy> mapFrom(const EnemyDto &) const override;

    [[nodiscard]] std::string getKey() const override;
    [[nodiscard]] std::type_index getType() const override;

};

using BaseEnemySuperMapper = SubtypeMapperAdapter<IEnemy, std::unique_ptr<IEnemy>, BaseEnemyMapper>;

