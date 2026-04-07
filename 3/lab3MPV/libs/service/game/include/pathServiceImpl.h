#pragma once
#include "castle/include/castle.h"
#include "map/include/map.h"
#include "model/service/game/PathCalcService.h"
#include "castle/include/castle.h"

/**
 * сервисрасчета приоритетов и векторов для карты
 */
class PathCalcServiceImpl : public PathCalcService {
    Map & map;
    Castle & castle;
    public:
    PathCalcServiceImpl(Map & map_, Castle & castle_);
    void calcFlowForMap() override;///< обходв ширину от замка

    void calcDistanceForMap() override;///< подсчет грвдиента для мапы

};