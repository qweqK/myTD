#pragma once
#include "model/../../containerClass/Matrix.h"
#include "cell/include/cell.h"

/**
 * класс, для описания карты
 */
class Map {
    Matrix<Cell> cells;///< массив клеток
    public:
    Map(size_t  length, size_t width, std::initializer_list<Cell> list);///< конструктор через лист инициализации

    Map(size_t width, size_t height, std::vector<Cell>); ///< конструктор через вектор клеток
    Map() =default;
    Matrix<Cell> &get();///< получить матрицу клеток
    Cell &at(size_t x, size_t y);///< доступ к клетке (x,y)
    [[nodiscard]]size_t getRows() const;
    [[nodiscard]]size_t getCols() const;
    [[nodiscard]] Matrix<Cell>& getCells();
    [[nodiscard]] size_t getSize() const;



};