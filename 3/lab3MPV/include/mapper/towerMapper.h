#pragma once

#include <memory>

#include "polymorphicMapper.h"
#include "mapper.h"
#include "model/tower/Tower.h"
#include "dto/TowerDto.h"

using TowerMapper= Mapper<ITower, TowerDTO, std::unique_ptr<ITower>>;

template<typename Subtype>
using ConcreteTowerMapper= SubtypeMapper<Subtype, TowerDTO, std::unique_ptr<Subtype>>;

template<typename ConcreteMapper>
using SuperTowerMapper=SubtypeMapperAdapter<ITower, TowerDTO, ConcreteMapper>;

class PolymorphicTowerMapper final : public PolymorphicMapper<ITower, TowerDTO, std::unique_ptr<ITower>> {
    public:
    [[nodiscard]] std::string getKey(const TowerDTO &dto) const override {
        return dto.type;
    }
};
