#pragma once
#include "mapper.h"
#include "polymorphicMapper.h"
#include "dto/EnemyDto.h"
#include "model/enemy/Enemy.h"
using EnemyMapper= Mapper<IEnemy, EnemyDto, std::unique_ptr<IEnemy>>;

template<typename Subtype>
using ConcreteEnemyMapper=SubtypeMapper<Subtype, EnemyDto, std::unique_ptr<Subtype>>;

template<typename ConcreteMapper>
using SuperEnemyMapper = SubtypeMapperAdapter<IEnemy, EnemyDto, ConcreteMapper>;

class PolymorphicEnemyMapper final : public PolymorphicMapper<IEnemy, EnemyDto, std::unique_ptr<IEnemy>> {
    public:
    [[nodiscard]] std::string getKey(const EnemyDto &dto) const override {
        return dto.type;
    }
};



