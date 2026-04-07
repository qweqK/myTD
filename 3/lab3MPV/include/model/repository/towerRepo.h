#pragma once
#include "REPO.h"
#include "model/tower/Tower.h"

/**
 * хранение башен
 */
class TowerRepository : public  REPO<ITower> {
public:
    using TowerPtr = std::unique_ptr<ITower>;
    virtual void removeDead()=0;

};