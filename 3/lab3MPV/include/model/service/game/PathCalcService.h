#pragma once

/**
 * сервис расчета пути
 */
class PathCalcService {
    public:
    virtual ~PathCalcService()=default;
    virtual void calcDistanceForMap()=0;///< расчет приоритета клеток
    virtual void calcFlowForMap()=0;///< расчет векторов для ходьбы
};
