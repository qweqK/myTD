#pragma once
#include "registry.h"
#include "model/enemy/Enemy.h"


/**
 * класс для хранение типов врагов
 */
class EnemyTypeRegistry : public Registry<IEnemy, std::string>  {

};
