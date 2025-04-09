#ifndef GAME_H
#define GAME_H

#include "Library.h"
#include "Tetromino.h"

class Game {
public:
    std::vector<std::vector<int>> currentBoard;
    std::vector<std::vector<int>> landedBoard;
public:
    TetrominoParent* currentTetromino;
public:
    int point;
    std::vector<int> speedLevel = {true, true, true, true, true, true, true, true, true, true, true, true, true};
public:
    Game();
    ~Game();
public:
    TetrominoParent* randomTetromino();
public:
    void updateCurrentBoard();
};

#endif
