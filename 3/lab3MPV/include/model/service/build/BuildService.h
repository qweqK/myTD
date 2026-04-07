#pragma once
#include <typeindex>

//#include "model/point/point.h"
#include "model/tower/Tower.h"

/**
 * абстраеный сервис для постройки башен
 */
class BuildService {
    public:
    virtual ~BuildService() = default;
    virtual bool tryBuildTower(Point pos, const std::string & name)=0;///< попытка постройкт
    virtual void sellTower(ITower *tower)=0;///< продажа
    virtual bool levelUp(ITower *tower)=0;///< левел ап

};
