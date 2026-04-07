#pragma once

#include "mapper/towerMapper.h"
#include "magickTower.h"
#include "model/repository/effectRegistry.h"
#include "model/repository/attackRegistry.h"
#include "model/repository/findTargetRegistry.h"

class MagickTowerMapper : public ConcreteTowerMapper<MagickTower> {
    AttackRegistry & attackRegistry;
    EffectRegistry & effectRegistry;
    FindTargetRegistry & shootRegistry;

    public:
    MagickTowerMapper(AttackRegistry & aReg, EffectRegistry& eReg, FindTargetRegistry & sReg) : attackRegistry(aReg), effectRegistry(eReg), shootRegistry(sReg) {}
    [[nodiscard]] TowerDTO mapTo(const MagickTower &) const override;
    [[nodiscard]] std::unique_ptr<MagickTower> mapFrom(const TowerDTO &) const override;

    [[nodiscard]] std::string getKey() const override;
    [[nodiscard]] std::type_index getType() const override;
};

using MagickTowerSuperMapper = SubtypeMapperAdapter<ITower, std::unique_ptr<ITower>, MagickTowerMapper>;

