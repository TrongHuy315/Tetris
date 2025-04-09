#ifndef MAIN_H
#define MAIN_H

#include "Library.h"
#include "TetrominoParent.h"
#include "Tetromino.h"
#include "Game.h"

sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE + 200, HEIGHT * CELL_SIZE), "Tetris Game");

sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

clock_t start = clock();
double interval = 0.8;

Game object;

std::vector<TetrominoParent*> nextQueue;

void refillNextQueue() {
    while (nextQueue.size() < 5) {
        nextQueue.push_back(object.randomTetromino());
    }
}

sf::Color numberToColor(int num) {
    switch (num) {
        case 1: return sf::Color(255, 87, 34);
        case 2: return sf::Color(63, 81, 181);
        case 3: return sf::Color(255, 235, 59);
        case 4: return sf::Color(156, 39, 176);
        case 5: return sf::Color(76, 175, 80);
        case 6: return sf::Color(183, 28, 28);
        case 7: return sf::Color(0, 188, 212);
        default: throw std::abort;
    }
}

bool bottomOverLapped(TetrominoParent* tetromino) {
    if (object.currentTetromino->shape[tetromino->angle].size() + tetromino->row > HEIGHT) return true;

    return false;
}

bool landedOverLapped(TetrominoParent* tetromino) {
    int height = object.currentTetromino->shape[tetromino->angle].size();
    int width = object.currentTetromino->shape[tetromino->angle][0].size();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (object.currentTetromino->shape[tetromino->angle][i][j] > 0 && object.landedBoard[tetromino->row + i][tetromino->col + j] > 0) return true;
        }
    }

    return false;
}

void mergeCurrentTetromino() {
    int height = object.currentTetromino->shape[object.currentTetromino->angle].size();
    int width = object.currentTetromino->shape[object.currentTetromino->angle][0].size();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (object.currentTetromino->shape[object.currentTetromino->angle][i][j] > 0) {
                object.landedBoard[object.currentTetromino->row + i][object.currentTetromino->col + j] = object.currentTetromino->shape[object.currentTetromino->angle][i][j];
            }
        }
    }
}

std::vector<int> findRowCanClear() {
    std::vector<int> result;
    for (int i = HEIGHT - 1; i > 3; i--) {
        bool flag = true;
        for (int j = 0; j < WIDTH; j++) {
            if (object.landedBoard[i][j] == 0) {
                flag = false;
                break;
            }
        }

        if (flag) result.push_back(i);
    }

    return result;
}

void clearRow(std::vector<int> arr) {
    for (int k = arr.size() - 1; k >= 0; k--) {
        for (int i = arr[k]; i > 3; i--) {
            for (int j = 0; j < WIDTH; j++) {
                object.landedBoard[i][j] = object.landedBoard[i - 1][j];
            }
        }
    }
}

int calculateScore(int rowsCount) {
    return (rowsCount * (rowsCount + 1)) / 2;
}

void progress() {
    TetrominoParent* temp = new TetrominoParent(object.currentTetromino->row + 1, object.currentTetromino->col, object.currentTetromino->angle);
    if (!bottomOverLapped(temp) && !landedOverLapped(temp)) {
        object.currentTetromino->fall();
    }
    else {
        mergeCurrentTetromino();

        std::vector<int> sub = findRowCanClear();
        clearRow(sub);
        object.point += calculateScore(sub.size());

        object.currentTetromino = nextQueue.front();
        nextQueue.erase(nextQueue.begin());
        refillNextQueue();
    }

    delete temp;
}

void tryMoveDown() {
    progress();
    object.updateCurrentBoard();
}

bool leftOverLapped(TetrominoParent* tetromino) {
    if (tetromino->col < 0) return true;
    
    return false;
}

bool rightOverLapped(TetrominoParent* tetromino) {
    if (tetromino->col + object.currentTetromino->shape[tetromino->angle][0].size() > WIDTH) return true;

    return false;
}

void tryMoveLeft() {
    TetrominoParent* temp = new TetrominoParent(object.currentTetromino->row, object.currentTetromino->col - 1, object.currentTetromino->angle);
    if (!leftOverLapped(temp) && !landedOverLapped(temp)) {
        object.currentTetromino->move(-1);
        object.updateCurrentBoard();
    }

    delete temp;
}

void tryMoveRight() {
    TetrominoParent* temp = new TetrominoParent(object.currentTetromino->row, object.currentTetromino->col + 1, object.currentTetromino->angle);
    if (!rightOverLapped(temp) && !landedOverLapped(temp)) {
        object.currentTetromino->move(1);
        object.updateCurrentBoard();
    }

    delete temp;
}

void tryRotate() {
    TetrominoParent* temp = new TetrominoParent(object.currentTetromino->row, object.currentTetromino->col, object.currentTetromino->angle);
    temp->rotate();
    if (!leftOverLapped(temp) && !rightOverLapped(temp) && !landedOverLapped(temp)) {
        object.currentTetromino->rotate();
        object.updateCurrentBoard();
    }
}

void tryMoveLand() {
    while (true) {
        TetrominoParent* temp = new TetrominoParent(object.currentTetromino->row + 1, object.currentTetromino->col, object.currentTetromino->angle);
        if (bottomOverLapped(temp) || landedOverLapped(temp)) {
            delete temp;
            break;
        }

        delete temp;
        object.currentTetromino->fall();
    }

    mergeCurrentTetromino();

    std::vector<int> sub = findRowCanClear();
    clearRow(sub);
    object.point += calculateScore(sub.size());
    object.currentTetromino = nextQueue.front();
    nextQueue.erase(nextQueue.begin());
    refillNextQueue();
    object.updateCurrentBoard();
}

int imageIndexOfCurrentTetromino() {
    int k = 1;
    while (true) {
        TetrominoParent* temp = new TetrominoParent(object.currentTetromino->row + k, object.currentTetromino->col, object.currentTetromino->angle);
        if (bottomOverLapped(temp) || landedOverLapped(temp)) {
            delete temp;
            break;
        }

        k++;
    }

    return k - 1;
}

bool isGameOver() {
    for (int i = 0; i < WIDTH; i++) {
        if (object.landedBoard[3][i] > 0) return true;
    }

    return false;
}

void updateSpeed() {
    if (object.speedLevel[object.point / 10]) {
        object.speedLevel[object.point / 10] = false;
        interval -= 0.1;
    }
}

void displayGameOverMessage(sf::RenderWindow& window, const std::string& message) {
    sf::Font font;
    if (!font.loadFromFile("../arial.ttf")) {
        std::cerr << "Cannot load font!" << std::endl;
        return;
    }

    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x, 100.f));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(0.f, window.getSize().y / 2.f - 50.f);

    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        (window.getSize().x - textBounds.width) / 2.f,
        window.getSize().y / 2.f - textBounds.height / 2.f
    );

    window.clear(sf::Color::Black);
    window.draw(rectangle);
    window.draw(text);
    window.display();
}

bool showPlayAgainMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../arial.ttf")) {
        std::cerr << "Cannot load font!" << std::endl;
        return false;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Play Again? (Y/N)");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 20);

    sf::Event event;
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Y) {
                    return true;
                } else if (event.key.code == sf::Keyboard::N) {
                    return false;
                }
            }
        }
    }
    return false;
}

void resetGame() {
    object.point = 0;
    object.currentTetromino = object.randomTetromino();
    object.currentBoard = std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, 0));
    object.landedBoard = std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, 0));
    start = clock();
}

#endif
