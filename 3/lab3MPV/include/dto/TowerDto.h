#pragma once
#include <string>
#include  <map>
#include "../model/point/point.h"


/**
 * структура описывающааа башню в дто
 */
struct TowerDTO {
    std::string type;///< ее тип
    int level;///< ее лвл
    int cost; ///< ее стоимость
    int xPos, yPos; ///< ее местоположение
    std::string attackStrategy; ///< стратегия атаки
    int range; ///<радиус
    float levelMulty; ///< множитель лвла

    std::map<std::string , std::string > properties; ///< ее свойства

};
