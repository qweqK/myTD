#pragma once
#include <string>
#include  <map>
#include <nlohmann/json.hpp>

#include "model/point/point.h"

/**
 * структура описывающааа врага в DTO
 */
struct EnemyDto {
    std::string name;///<имя врагаа
    std::string type; ///<тип вараг
    float curHp; ///< текущее кол во хп
    float maxHp; ///< макс хп
    float speed; /// макс спид
    float posX; ///< позX
    float posY; ///< позУ
    int gold; ///< число дееняк
    std::map<std::string, std::pair<float, float>> effectTable; ///<таблицы эффектов
};

