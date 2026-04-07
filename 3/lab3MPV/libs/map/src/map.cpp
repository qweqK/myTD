#include "map.h"

Map::Map(size_t length, size_t width, std::initializer_list<Cell> list) : cells(width, length, list){}


Map::Map(size_t width, size_t height, std::vector<Cell> cel) {
    Matrix<Cell> cellss{height, width, cel.begin(), cel.end()};

    cells= std::move(cellss);
}


Cell &Map::at(size_t x, size_t y) {
    return cells[y][x];
}

Matrix<Cell> &Map::get() {
    return cells;
}

size_t Map::getRows() const {
    return cells.height();
}

size_t Map::getCols() const {
    return cells.width();
}

 Matrix<Cell> &Map::getCells(){
    return cells;
}

size_t Map::getSize() const {
    return cells.size();
}




