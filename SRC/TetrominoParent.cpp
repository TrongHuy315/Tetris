#include "../HEADERS/TetrominoParent.h"

TetrominoParent::TetrominoParent(int row, int col, int angle = 0) {
    this->row = row;
    this->col = col;
    this->angle = angle;
}

TetrominoParent::~TetrominoParent() {}

void TetrominoParent::move(int direction) {
    if (direction == -1) this->col -= 1;
    else this->col += 1;
}

void TetrominoParent::fall() {
    this->row += 1;
}

void TetrominoParent::rotate() {
    this->angle = (++this->angle) % 4;
}
