#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace sf;
using namespace std;

const int fieldHeight = 15, fieldWidth = 15, tileSize = 32, tileAmount = 5, figureAmount = 8, addCoord = 10000;
int field[fieldHeight][fieldWidth];

void fieldFill(int field[fieldHeight][fieldWidth]) {

    int numberOfLine, numberOfRow;

    for (numberOfLine = 0; numberOfLine < fieldHeight; ++numberOfLine) {
        for (numberOfRow = 0; numberOfRow < fieldWidth; ++numberOfRow) {
            field[numberOfLine][numberOfRow] = figureAmount;
        }
    }
}

struct tilePosition {

    int x, y;

} tileCoords[tileAmount], previousCoords[tileAmount], axis;

int localTileCoords[figureAmount][tileAmount] = {
    1,3,5,7,0,
    2,4,5,7,0,
    3,5,4,6,0,
    3,5,4,7,0,
    2,3,5,7,0,
    3,5,7,6,0,
    2,3,4,5,0,
    3,5,7,6,2

};

void collisionX(tilePosition currentCoords[tileAmount], tilePosition previousCoords[tileAmount]) {

    int numberOfTile, neededTileAmount;

    if (tileCoords[4].x == addCoord) {
        neededTileAmount = tileAmount - 1;
    } else {
        neededTileAmount = tileAmount;
    }

    for (numberOfTile = 0; numberOfTile < neededTileAmount; ++numberOfTile) {
        if (currentCoords[numberOfTile].x < 0 || currentCoords[numberOfTile].x >= fieldWidth || field[currentCoords[numberOfTile].y][currentCoords[numberOfTile].x] != figureAmount) {
            for (numberOfTile = 0; numberOfTile < neededTileAmount; ++numberOfTile) {
                currentCoords[numberOfTile] = previousCoords[numberOfTile];
            }
            break;
        }
    }
}

void collisionY(tilePosition currentCoords[tileAmount], tilePosition previousCoords[tileAmount], int field[fieldHeight][fieldWidth], int figure, bool* figureIsPlaced) {

    int numberOfTile, neededTileAmount;

    if (tileCoords[4].x == addCoord) {
        neededTileAmount = tileAmount - 1;
    } else {
        neededTileAmount = tileAmount;
    }

    for (numberOfTile = 0; numberOfTile < neededTileAmount; ++numberOfTile) {
        if (tileCoords[numberOfTile].x == addCoord) {
            break;
        }

        if (currentCoords[numberOfTile].y >= fieldHeight || field[currentCoords[numberOfTile].y][currentCoords[numberOfTile].x] != figureAmount) {
            for (numberOfTile = 0; numberOfTile < neededTileAmount; ++numberOfTile) {
                field[currentCoords[numberOfTile].y - 1][currentCoords[numberOfTile].x] = figure;
            }

            *figureIsPlaced = true;

            break;
        }
    }
}

void deleteLine(int field[fieldHeight][fieldWidth], bool* lineIsFinished, bool* gameOver, int* score) {

    int numberOfLine, numberOfTile, lineIndex, tileIndex, filledTilesCount = 0, finishedLineCount = 0;

    for (numberOfLine = 0; numberOfLine < fieldHeight; ++numberOfLine) {
        for (numberOfTile = 0; numberOfTile < fieldWidth; ++numberOfTile) {
            if (field[numberOfLine][numberOfTile] != figureAmount) {
                if (numberOfLine == 0) {
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

            ++finishedLineCount;
        }

        filledTilesCount = 0;
    }

    switch (finishedLineCount) {
        case 1: {
            *score += 40;

            break;
        }
        case 2: {
            *score += 100;

            break;
        }
        case 3: {
            *score += 300;

            break;
        }
        case 4: {
            *score += 1200;

            break;
        }
        default: {
        }
    }
}

int main() {

    srand(time(0));

    RenderWindow window(VideoMode(fieldWidth * tileSize, fieldHeight * tileSize), "Tetris");
    window.setVerticalSyncEnabled(true);

    Texture tTiles, tBackground;
    tTiles.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/images/tiles.png");
    tBackground.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/images/background.png");
    Sprite tile(tTiles), background(tBackground);

    Font font;
    font.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/fonts/karma_suture.ttf");

    Text currentScore, highestScore, speed;
    currentScore.setFont(font);
    highestScore.setFont(font);
    speed.setFont(font);
    currentScore.setCharacterSize(20);
    highestScore.setCharacterSize(20);
    speed.setCharacterSize(15);
    currentScore.setFillColor(Color::White);
    highestScore.setFillColor(Color::White);
    speed.setFillColor(Color::White);
    currentScore.setPosition(0, 0);
    highestScore.setPosition(0, 25);
    speed.setPosition(350, 440);

    int figureType = 0, numberOfTile, numberOfLine, direction = 0, x, y, score = 0;

    Clock clock;

    float delay = 0.5, tempDelay, time, timer = 0;

    bool figureIsPlaced = false, lineIsFinished = false, gameOver = false, rotation = false, nextFigure = true;

    string tCurrentScore, tHighestScore, tSpeed, record;

    ifstream iScore("C:/Users/aveng/source/repos/Tetris/Tetris/score.txt");
    getline(iScore, record);
    iScore.close();

    fieldFill(field);

    while (window.isOpen()) {
        while (figureIsPlaced == false) {
            if (nextFigure == true) {
                figureType = rand() % figureAmount;
                if (figureType == 7) {
                    for (numberOfTile = 0; numberOfTile < tileAmount; ++numberOfTile) {
                        nextFigure = false;

                        tileCoords[numberOfTile].x = localTileCoords[figureType][numberOfTile] % 2;
                        tileCoords[numberOfTile].y = localTileCoords[figureType][numberOfTile] / 2;
                    }
                } else {
                    for (numberOfTile = 0; numberOfTile < tileAmount - 1; ++numberOfTile) {
                        nextFigure = false;

                        tileCoords[numberOfTile].x = localTileCoords[figureType][numberOfTile] % 2;
                        tileCoords[numberOfTile].y = localTileCoords[figureType][numberOfTile] / 2;
                    }

                    tileCoords[4].x = addCoord;
                    tileCoords[4].y = addCoord;
                }
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
                        rotation = true;
                    }
                    else if (event.key.code == Keyboard::Right) {
                        direction = 1;
                    }
                    else if (event.key.code == Keyboard::Left) {
                        direction = -1;
                    }
                    else if (event.key.code == Keyboard::Down) {
                        delay = 0.03;
                    }
                }
            }

            for (numberOfTile = 0; numberOfTile < tileAmount; ++numberOfTile) {
                if (tileCoords[numberOfTile].x == addCoord) {
                    break;
                }

                previousCoords[numberOfTile] = tileCoords[numberOfTile];
                tileCoords[numberOfTile].x += direction;
            }
            collisionX(tileCoords, previousCoords);
            direction = 0;

            if (rotation == true) {
                axis = tileCoords[1];
                for (numberOfTile = 0; numberOfTile < tileAmount; ++numberOfTile) {
                    if (tileCoords[numberOfTile].x == addCoord) {
                        break;
                    }

                    x = tileCoords[numberOfTile].y - axis.y;
                    y = tileCoords[numberOfTile].x - axis.x;

                    tileCoords[numberOfTile].x = axis.x - x;
                    tileCoords[numberOfTile].y = axis.y + y;
                }
                collisionX(tileCoords, previousCoords);

            }
            rotation = false;

            if (timer >= delay) {
                for (numberOfTile = 0; numberOfTile < tileAmount; ++numberOfTile) {
                    if (tileCoords[numberOfTile].x == addCoord) {
                        break;
                    }

                    tileCoords[numberOfTile].y += 1;
                }
                timer = 0;
            }
            delay = tempDelay;

            collisionY(tileCoords, previousCoords, field, figureType, &figureIsPlaced);
            deleteLine(field, &lineIsFinished, &gameOver, &score);

            if (score > stoi(record)) {
                record = to_string(score);
            }

            window.clear();
            window.draw(background);
            for (numberOfTile = 0; numberOfTile < tileAmount; ++numberOfTile) {
                if (tileCoords[numberOfTile].x == addCoord) {
                    break;
                }

                tile.setTextureRect(IntRect(figureType * tileSize, 0, tileSize, tileSize));
                tile.setPosition(tileCoords[numberOfTile].x * tileSize, tileCoords[numberOfTile].y * tileSize);
                window.draw(tile);
            }
            for (numberOfLine = 0; numberOfLine < fieldHeight; ++numberOfLine) {
                for (numberOfTile = 0; numberOfTile < fieldWidth; ++numberOfTile) {
                    if (field[numberOfLine][numberOfTile] != figureAmount) {
                        tile.setTextureRect(IntRect(field[numberOfLine][numberOfTile] * tileSize, 0, tileSize, tileSize));
                        tile.setPosition(numberOfTile * tileSize, numberOfLine * tileSize);
                        window.draw(tile);
                    }
                }
            }
            tCurrentScore = "Score: " + to_string(score);
            tHighestScore = "Highest score: " + record;
            tSpeed = "Speed: " + to_string(delay);
            currentScore.setString(tCurrentScore);
            window.draw(currentScore);
            highestScore.setString(tHighestScore);
            window.draw(highestScore);
            speed.setString(tSpeed);
            window.draw(speed);

            window.display();
        }

        if (delay >= 0.2 && lineIsFinished == true) {
            delay -= 0.06;
        }

        if (gameOver == true) {
            fieldFill(field);

            score = 0;

            delay = 0.5;

            gameOver = false;
        }

        figureIsPlaced = false;
        lineIsFinished = false;
        nextFigure = true;

        ofstream oScore("C:/Users/aveng/source/repos/Tetris/Tetris/score.txt");
        oScore << record;
        oScore.close();
    }

    return 0;
}
