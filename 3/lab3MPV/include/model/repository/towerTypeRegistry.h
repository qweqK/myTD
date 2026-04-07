#pragma once

#include "registry.h"
#include "model/tower/Tower.h"

/**
 * реестр типов башен
 */
class TowerTypeRegistry: public Registry<ITower, std::string> {

};
