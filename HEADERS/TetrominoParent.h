#ifndef TETROMINOPARENT_H
#define TETROMINOPARENT_H

#include "Library.h"

class TetrominoParent {
public:
    int row;
    int col;
    int angle;
public:
    std::vector<std::vector<std::vector<int>>> shape;
public:
    TetrominoParent(int, int, int);
    ~TetrominoParent();
public:
    void fall();
    void rotate();
    void move(int);
};

#endif
