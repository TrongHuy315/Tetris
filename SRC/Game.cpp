#include "../HEADERS/Game.h"

Game::Game() {
    this->currentTetromino = randomTetromino();
    this->point = 0;
    
    for (int i = 0; i < HEIGHT; i++) {
        std::vector<int> sub;
        for (int j = 0; j < WIDTH; j++) {
            sub.push_back(0);
        }

        this->currentBoard.push_back(sub);
    }

    for (int i = 0; i < HEIGHT; i++) {
        std::vector<int> sub;
        for (int j = 0; j < WIDTH; j++) {
            sub.push_back(0);
        }

        this->landedBoard.push_back(sub);
    }
}

Game::~Game() {}

TetrominoParent* Game::randomTetromino() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 7);

    int rand = dist(gen);

    switch(rand) {
        case 1:
            return new LShape(1, 4);
        case 2:
            return new JShape(1, 4);
        case 3:
            return new OShape(2, 4);
        case 4:
            return new TShape(2, 4);
        case 5:
            return new SShape(2, 4);
        case 6:
            return new ZShape(2, 4);
        case 7:
            return new IShape(0, 4);
        default:
            throw std::abort;
    }
}

void Game::updateCurrentBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            this->currentBoard[i][j] = this->landedBoard[i][j];
        }
    }

    int tetroHeight = this->currentTetromino->shape[this->currentTetromino->angle].size();
    int tetroWidth = this->currentTetromino->shape[this->currentTetromino->angle][0].size();

    for (int i = 0; i < tetroHeight; i++) {
        for (int j = 0; j < tetroWidth; j++) {
            if (this->currentTetromino->shape[this->currentTetromino->angle][i][j] > 0) {
                this->currentBoard[this->currentTetromino->row + i][this->currentTetromino->col + j] = this->currentTetromino->shape[this->currentTetromino->angle][i][j];
            }
        }
    }
}
