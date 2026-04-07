#pragma once
#include "mapper.h"
#include "model/enemy/Enemy.h"
#include "lair/include/lair.h"
#include "dto/LairDto.h"
#include "mapper/polymorphicMapper.h"


using LairMapper = Mapper<Lair, LairDTO, std::unique_ptr<Lair>>;

template<typename Subtype>
using ConcreteLairMapper = SubtypeMapper<Subtype, LairDTO, std::unique_ptr<Subtype>>;

template<typename ConcreteMapper>
using SuperLairMapper = SubtypeMapperAdapter<Lair, LairDTO, ConcreteMapper>;

class PolymorphicLairMapper : public PolymorphicMapper<Lair, LairDTO, std::unique_ptr<Lair>> {
    public:
    [[nodiscard]] std::string getKey(const LairDTO &dto) const override {
        return dto.type;
    }
};
