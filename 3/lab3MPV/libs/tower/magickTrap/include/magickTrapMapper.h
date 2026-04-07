#pragma once
#include "mapper/towerMapper.h"
#include "magickTrap.h"
#include "model/repository/effectRegistry.h"
#include "model/repository/attackRegistry.h"
class MagickTrapMapper : public ConcreteTowerMapper<MagickTrap> {
   EffectRegistry &effectRegistry;
    AttackRegistry &attackRegistry;

    public:
    explicit MagickTrapMapper(EffectRegistry &eReg, AttackRegistry &aReg) :effectRegistry(eReg), attackRegistry(aReg){}

    [[nodiscard]] TowerDTO mapTo(const MagickTrap &) const override;
    [[nodiscard]] std::unique_ptr<MagickTrap> mapFrom(const TowerDTO &) const override;

    [[nodiscard]] std::string getKey() const override;
    [[nodiscard]] std::type_index getType() const override;


};

using MagickTrapSupperMapper = SubtypeMapperAdapter<ITower, std::unique_ptr<ITower>, MagickTrapMapper>;
