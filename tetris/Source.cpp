#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int fieldLenght = 20, fieldWidth = 10, tileSize = 32;

int field[fieldLenght][fieldWidth];

void fieldFill(int field[fieldLenght][fieldWidth]) {

    int numberOfLine, numberOfRow;

    for (numberOfLine = 0; numberOfLine < fieldLenght; ++numberOfLine) {

        for (numberOfRow = 0; numberOfRow < fieldWidth; ++numberOfRow) {

            field[numberOfLine][numberOfRow] = 7;
        }
    }
}

struct tilePosition {
    int x, y;
} tileCoords[4], previousCoords[4];

void startTileCoords(tilePosition tileCoords[4], int figureType) {
    switch (figureType) {
        case 0: {
            tileCoords[0].x = 0;
            tileCoords[0].y = 0;
            tileCoords[1].x = 1;
            tileCoords[1].y = 0;
            tileCoords[2].x = 2;
            tileCoords[2].y = 0;
            tileCoords[3].x = 3;
            tileCoords[3].y = 0;

            break;
        }
        case 1: {
            tileCoords[0].x = 0;
            tileCoords[0].y = 0;
            tileCoords[1].x = 0;
            tileCoords[1].y = 1;
            tileCoords[2].x = 1;
            tileCoords[2].y = 1;
            tileCoords[3].x = 2;
            tileCoords[3].y = 1;

            break;
        }
        case 2: {
            tileCoords[0].x = 0;
            tileCoords[0].y = 1;
            tileCoords[1].x = 1;
            tileCoords[1].y = 1;
            tileCoords[2].x = 2;
            tileCoords[2].y = 1;
            tileCoords[3].x = 2;
            tileCoords[3].y = 0;

            break;
        }
        case 3: {
            tileCoords[0].x = 0;
            tileCoords[0].y = 0;
            tileCoords[1].x = 0;
            tileCoords[1].y = 1;
            tileCoords[2].x = 1;
            tileCoords[2].y = 0;
            tileCoords[3].x = 1;
            tileCoords[3].y = 1;

            break;
        }
        case 4: {
            tileCoords[0].x = 0;
            tileCoords[0].y = 1;
            tileCoords[1].x = 1;
            tileCoords[1].y = 1;
            tileCoords[2].x = 1;
            tileCoords[2].y = 0;
            tileCoords[3].x = 2;
            tileCoords[3].y = 0;

            break;
        }
        case 5: {
            tileCoords[0].x = 0;
            tileCoords[0].y = 1;
            tileCoords[1].x = 1;
            tileCoords[1].y = 1;
            tileCoords[2].x = 1;
            tileCoords[2].y = 0;
            tileCoords[3].x = 2;
            tileCoords[3].y = 1;

            break;
        }
        case 6: {
            tileCoords[0].x = 0;
            tileCoords[0].y = 0;
            tileCoords[1].x = 1;
            tileCoords[1].y = 0;
            tileCoords[2].x = 1;
            tileCoords[2].y = 1;
            tileCoords[3].x = 2;
            tileCoords[3].y = 1;

            break;
        }
    }
}

int localTileCoords[7][4] = {
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};

void rotation(tilePosition currentCoords[4]) {

    tilePosition axis = currentCoords[1];

    int numberOfTile, x, y;

    for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

        x = currentCoords[numberOfTile].y - axis.y;
        y = currentCoords[numberOfTile].x - axis.x;

        currentCoords[numberOfTile].x = axis.x - x;
        currentCoords[numberOfTile].y = axis.y - y;
    }
}

void collisionX(tilePosition currentCoords[4], tilePosition previousCoords[4]) {

    int numberOfTile;

    for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

        if (currentCoords[numberOfTile].x < 0 || currentCoords[numberOfTile].x >= fieldWidth || field[currentCoords[numberOfTile].y][currentCoords[numberOfTile].x] != 7) {
            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                currentCoords[numberOfTile] = previousCoords[numberOfTile];
            }

            break;
        }
    }
}

void collisionY(tilePosition currentCoords[4], tilePosition previousCoords[4], int field[fieldLenght][fieldWidth], int figure, bool* figureIsPlaced) {

    int numberOfTile;

    for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

        if (currentCoords[numberOfTile].y >= fieldLenght || field[currentCoords[numberOfTile].y][currentCoords[numberOfTile].x] != 7) {
            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                field[currentCoords[numberOfTile].y - 1][currentCoords[numberOfTile].x] = figure;
            }

            *figureIsPlaced = true;

            break;
        }
    }
}

void deleteLine(int field[fieldLenght][fieldWidth], bool* lineIsFinished, bool* gameOver) {

    int numberOfLine, numberOfTile, lineIndex, tileIndex, filledTilesCount = 0;

    for (numberOfLine = 0; numberOfLine < fieldLenght; ++numberOfLine) {

        for (numberOfTile = 0; numberOfTile < fieldWidth; ++numberOfTile) {

            if (field[numberOfLine][numberOfTile] != 7) {
                if (numberOfLine == 1) {
                    *gameOver = true;

                    return;
                }

                ++filledTilesCount;
            }
        }

        if (filledTilesCount == fieldWidth) {
            *lineIsFinished = true;

            for (lineIndex = numberOfLine; lineIndex > 0; --lineIndex) {

                for (tileIndex = 0; tileIndex < fieldWidth; ++tileIndex) {

                    field[lineIndex][tileIndex] = field[lineIndex - 1][tileIndex];
                }
            }
        }

        filledTilesCount = 0;
    }
}

int main() {

    srand(time(0));

    RenderWindow window(VideoMode(fieldWidth * tileSize, fieldLenght * tileSize), "Tetris");
    window.setVerticalSyncEnabled(true);

    Texture tTiles, tBackground, tGameOver;
    tTiles.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/images/tiles.png");
    tBackground.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/images/tiles.png");
    tGameOver.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/images/gameover.png");

    Sprite tile(tTiles), background(tBackground), gameIsOver(tGameOver);

    int figureType = 0, numberOfTile, numberOfLine, direction = 0;

    Clock clock;
    float delay = 0.5, tempDelay, time, timer = 0;

    bool figureIsPlaced = false, lineIsFinished = false, gameOver = false, rotate = false, nextFigure = true;

    fieldFill(field);

    while (window.isOpen()) {

        while (figureIsPlaced == false) {

            if (nextFigure == true) {

                nextFigure = false;

                figureType = rand() % 7;

                startTileCoords(tileCoords, figureType);
            }

            time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            tempDelay = delay;

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Up) {
                        //rotation(tileCoords);
                        rotate = true;
                    }
                    else if (event.key.code == Keyboard::Right) {
                        direction = 1;
                    }
                    else if (event.key.code == Keyboard::Left) {
                        direction = -1;
                    }
                    else if (event.key.code == Keyboard::Down) {
                        delay = 0.05;
                    }
                }
            }

            if (rotate == true) {

                tilePosition axis = tileCoords[1];

                int x, y;

                for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                    x = tileCoords[numberOfTile].y - axis.y;
                    y = tileCoords[numberOfTile].x - axis.x;

                    tileCoords[numberOfTile].x = axis.x - x;
                    tileCoords[numberOfTile].y = axis.y - y;
                }
            }

            rotate = false;

            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                previousCoords[numberOfTile] = tileCoords[numberOfTile];

                tileCoords[numberOfTile].x += direction;
            }

            collisionX(tileCoords, previousCoords);

            direction = 0;

            if (timer >= delay) {
                for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                    tileCoords[numberOfTile].y += 1;
                    timer = 0;
                }
            }

            delay = tempDelay;

            collisionY(tileCoords, previousCoords, field, figureType, &figureIsPlaced);

            deleteLine(field, &lineIsFinished, &gameOver);

            window.clear(Color::White);

            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                tile.setTextureRect(IntRect(figureType * tileSize, 0, tileSize, tileSize));
                tile.setPosition(tileCoords[numberOfTile].x * tileSize, tileCoords[numberOfTile].y * tileSize);
                window.draw(tile);
            }

            for (numberOfLine = 0; numberOfLine < fieldLenght; ++numberOfLine) {

                for (numberOfTile = 0; numberOfTile < fieldWidth; ++numberOfTile) {

                    if (field[numberOfLine][numberOfTile] != 7) {
                        tile.setTextureRect(IntRect(field[numberOfLine][numberOfTile] * tileSize, 0, tileSize, tileSize));
                        tile.setPosition(numberOfTile * tileSize, numberOfLine * tileSize);
                        window.draw(tile);
                    }
                }
            }

            if (gameOver == true) {
                gameIsOver.setTextureRect(IntRect(0, 0, fieldWidth * tileSize, fieldWidth * tileSize));
                gameIsOver.setPosition(0, fieldLenght / 2 * fieldWidth * tileSize);
                window.draw(gameIsOver);
            }

            window.display();
        }

        if (delay >= 0.2 && lineIsFinished == true) {
            delay -= 0.03;
        }

        figureIsPlaced = false;
        lineIsFinished = false;
        nextFigure = true;
    }
    return 0;
}
