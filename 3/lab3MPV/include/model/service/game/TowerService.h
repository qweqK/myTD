#pragma once
#include "../../tower/Tower.h"
#include "../../enemy/Enemy.h"
/**
* @brief сервис для башен
*/
class TowerService {
    public:
    virtual ~TowerService()=default;
    virtual void updateTower(float dt)=0;///< обновление башен

};