#pragma once
#include "mapper/polymorphicMapper.h"
#include "mapper/towerMapper.h"
#include "baseTower.h"
#include "model/repository/attackRegistry.h"
#include "model/repository/findTargetRegistry.h"


class BaseTowerMapper : public ConcreteTowerMapper<BaseTower> {
        AttackRegistry& attackRegistry;
        FindTargetRegistry & shootReg;

    public:
       explicit  BaseTowerMapper(AttackRegistry &aReg, FindTargetRegistry &sReg) : attackRegistry(aReg), shootReg(sReg){}

       [[nodiscard]] TowerDTO mapTo(const BaseTower & from) const override;

       [[nodiscard]] std::unique_ptr<BaseTower> mapFrom(const TowerDTO &dto) const override;

       [[nodiscard]] std::string getKey() const override;

       [[nodiscard]] std::type_index getType() const override;



};

using BaseTowerSuperMapper = SubtypeMapperAdapter<ITower, std::unique_ptr<ITower>, BaseTowerMapper>;

