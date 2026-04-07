#pragma once
#include <complex.h>
#include <vector>
#include "model/buildings/Build.h"
#include "model/point/point.h"
#include "model/enemy/Enemy.h"

/**
 * @brief типы ткрритории
 */
enum class TerraType {
    road, field, forest
};

/**
 * @brief структура, опитсывающая одну клутку в мапе
 */
struct Cell {
    Cell()=default;
    Cell(Point newPos, TerraType terra);///<конструктор по позиции, и типу территории
    Point pos;///< позиция клетки
    TerraType type;///< тип территории
    IBuild* build;///< постройка на клетке
    [[nodiscard]]TerraType getTerra() const;///< получить тип территоии
    int priority=99999; ///< приориткт клетки
    PointF flow={0.f, 0.f}; ///< вектор направления, для движения врагов
    void setPriority(int newPriority); ///< приритет для клетки
    [[nodiscard]]int getPriority() const;
    [[nodiscard]]bool isContent() const; ///< елсть ли контент на клетке
    [[nodiscard]] IBuild *getBuild() const;
    void setContent(IBuild *newBuild); ///< поставить строение на клетку
    void deleteContent(); ///< удалить строение с клетки
};