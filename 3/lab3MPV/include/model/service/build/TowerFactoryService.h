#pragma once
#include <typeindex>


/**
 * класс для создание башен, путем клонирования башни из реестора
 */
class TowerFactoryService {
    public:
    virtual ~TowerFactoryService() = default;
    virtual void create(Point pos, const std::string & towerName) const=0;
};
