#include "../HEADERS/main.h"

int main() {
    sf::Font font;
    font.loadFromFile("../arial.ttf");

    refillNextQueue();

    while (window.isOpen()) {
        updateSpeed();

        clock_t now = clock();
        double elapsed_time = double(now - start) / CLOCKS_PER_SEC;
        if (elapsed_time >= interval) {
            progress();
            start = now;
        }

        object.updateCurrentBoard();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    tryMoveLeft();
                } else if (event.key.code == sf::Keyboard::Right) {
                    tryMoveRight();
                } else if (event.key.code == sf::Keyboard::Down) {
                    tryMoveDown();
                } else if (event.key.code == sf::Keyboard::X) {
                    tryRotate();
                } else if (event.key.code == sf::Keyboard::Space) {
                    tryMoveLand();
                }
            }
        }

        window.clear(sf::Color::White);

        // Vẽ khung ngoài game board
        sf::RectangleShape outerFrame(sf::Vector2f(WIDTH * CELL_SIZE, (HEIGHT - 4) * CELL_SIZE));
        outerFrame.setPosition(0, 4 * CELL_SIZE);
        outerFrame.setFillColor(sf::Color::Transparent);
        outerFrame.setOutlineColor(sf::Color::Black);
        outerFrame.setOutlineThickness(4.f);
        window.draw(outerFrame);

        // Vẽ lưới nền
        cell.setFillColor(sf::Color::Transparent);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::Black);
        for (int i = 4; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                window.draw(cell);
            }
        }

        // Vẽ các ô đã hạ xuống
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (object.currentBoard[i][j] > 0) {
                    cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    cell.setFillColor(numberToColor(object.currentBoard[i][j]));
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setOutlineThickness(1);
                    window.draw(cell);
                }
            }
        }

        // Vẽ ghost Tetromino (viền trắng mờ)
        int k = imageIndexOfCurrentTetromino();
        for (int i = 0; i < object.currentTetromino->shape[object.currentTetromino->angle].size(); i++) {
            for (int j = 0; j < object.currentTetromino->shape[object.currentTetromino->angle][0].size(); j++) {
                if (object.currentTetromino->shape[object.currentTetromino->angle][i][j] > 0) {
                    cell.setPosition((object.currentTetromino->col + j) * CELL_SIZE, (object.currentTetromino->row + i + k) * CELL_SIZE);
                    cell.setFillColor(sf::Color::Transparent);
                    cell.setOutlineColor(sf::Color(255, 255, 255, 128));
                    cell.setOutlineThickness(2.f);
                    window.draw(cell);
                }
            }
        }

        // Hiển thị điểm
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(object.point));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(WIDTH * CELL_SIZE + 20, 50);
        window.draw(scoreText);

        // Hiển thị tốc độ hiện tại
        sf::Text speedText;
        speedText.setFont(font);
        speedText.setString("Speed: Lv." + std::to_string(13 - std::count(object.speedLevel.begin(), object.speedLevel.end(), true)));
        speedText.setCharacterSize(24);
        speedText.setFillColor(sf::Color::Black);
        speedText.setPosition(WIDTH * CELL_SIZE + 20, 90);
        window.draw(speedText);

        // Hiển thị các Tetromino kế tiếp
        float previewX = WIDTH * CELL_SIZE + 20;
        float previewY = 150;
        for (int n = 0; n < 4 && n < nextQueue.size(); ++n) {
            auto tetro = nextQueue[n];
            auto& shape = tetro->shape[0];
            for (int i = 0; i < shape.size(); ++i) {
                for (int j = 0; j < shape[0].size(); ++j) {
                    if (shape[i][j] > 0) {
                        cell.setSize(sf::Vector2f(CELL_SIZE * 0.6f, CELL_SIZE * 0.6f));
                        cell.setPosition(previewX + j * CELL_SIZE * 0.6f, previewY + i * CELL_SIZE * 0.6f);
                        cell.setFillColor(numberToColor(shape[i][j]));
                        cell.setOutlineColor(sf::Color::Black);
                        cell.setOutlineThickness(1);
                        window.draw(cell);
                    }
                }
            }
            previewY += shape.size() * CELL_SIZE * 0.6f + 10;
        }
        cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));

        window.display();

        if (isGameOver()) {
            std::string message = "Game Over! Your Score: ";
            message += std::to_string(object.point);
            displayGameOverMessage(window, message);

            sf::sleep(sf::seconds(3));

            bool playAgain = showPlayAgainMenu(window);
            if (playAgain) {
                resetGame();
                refillNextQueue();
            } else {
                window.close();
            }
        }
    }

    return 0;
}
