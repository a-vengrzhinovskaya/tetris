#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

const int fieldLenght = 20, fieldWidth = 10, tileSize = 18;

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
} tileCoords[4], defaultCoords[4], previousCoords[4];

int localTileCoords[7][4] = {
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};

void rotation(int figureType, int* rotationState, tilePosition currentCoords[4], tilePosition defaultCoords[4]) {

    int numberOfTile;

    switch (figureType) {
        case 0: {
            switch (*rotationState) {
                case 0: {
                    currentCoords[1].x = defaultCoords[0].x - tileSize;
                    currentCoords[2].x = defaultCoords[0].x + tileSize;
                    currentCoords[3].x = defaultCoords[0].x + tileSize * 2;
                    for (numberOfTile = 1; numberOfTile < 4; ++numberOfTile) {
                        currentCoords[numberOfTile].y = defaultCoords[0].y;
                    }
                    
                    ++(*rotationState);

                    break;
                }
                case 1: {
                    for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {
                        currentCoords[numberOfTile].x = defaultCoords[numberOfTile].x;
                        currentCoords[numberOfTile].y = defaultCoords[numberOfTile].y;
                    }

                    *rotationState = 0;
                    
                    break;
                }
            }
        }
    }
}

void collision(tilePosition currentCoords[4], tilePosition previousCoords[4]) {
    int numberOfTile;

    for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {
        if (currentCoords[numberOfTile].x < 0 || currentCoords[numberOfTile].x > fieldWidth) {
            currentCoords[numberOfTile] = previousCoords[numberOfTile];
        }
    }
}

int main() {

    srand(time(0));

    RenderWindow window(VideoMode(fieldWidth * tileSize, fieldLenght * tileSize), "Tetris");
    window.setVerticalSyncEnabled(true);
    
    Texture tTiles, tBackground;
    tTiles.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/images/tiles.png");
    tBackground.loadFromFile("C:/Users/aveng/source/repos/Tetris/Tetris/images/tiles.png");

    Sprite tile(tTiles), background(tBackground);

    int figureType = 0, numberOfTile, numberOfLine, direction = 0, rotationState = 0;

    Clock clock;
    float delay = 0.5, time, timer = 0;

    bool figureIsPlaced = false;

    fieldFill(field);

    while (window.isOpen()) {
        while (figureIsPlaced == false) {
            if (tileCoords[0].y == 0) {

                figureType = rand() % 7;

                for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                    tileCoords[numberOfTile].x = localTileCoords[figureType][numberOfTile] % 2;
                    tileCoords[numberOfTile].y = localTileCoords[figureType][numberOfTile] / 2;

                    defaultCoords[numberOfTile].x = tileCoords[numberOfTile].x;
                    defaultCoords[numberOfTile].y = tileCoords[numberOfTile].y;
                }
            }

            time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Up) {
                        //++rotationState;
                        rotation(figureType, &rotationState, tileCoords, defaultCoords);
                        /*if (rotationState >= 4) {
                            rotationState = -1;
                        }*/
                    }
                    else if (event.key.code == Keyboard::Right) {
                        direction = 1;
                    }
                    else if (event.key.code == Keyboard::Left) {
                        direction = -1;
                    }/*else if (event.key.code == Keyboard::Down) {
                        delay =
                    }*/
                }
            }

            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                previousCoords[numberOfTile] = tileCoords[numberOfTile];

                tileCoords[numberOfTile].x += direction;
            }

            collision(tileCoords, previousCoords);

            direction = 0;

            if (timer >= delay) {
                for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                    tileCoords[numberOfTile].y += 1;
                    timer = 0;
                }
            }

            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                if (tileCoords[numberOfTile].y >= fieldLenght /* || field[tileCoords[numberOfTile].y][tileCoords[numberOfTile].x] != 8*/) {
                    for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                        field[tileCoords[numberOfTile].y][tileCoords[numberOfTile].x] = figureType;
                    }

                    figureIsPlaced = true;

                    break;
                }
            }

            window.clear(Color::White);

            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                tile.setTextureRect(IntRect(figureType * tileSize, 0, tileSize, tileSize));
                tile.setPosition(tileCoords[numberOfTile].x * tileSize, tileCoords[numberOfTile].y * tileSize);
                window.draw(tile);
            }

            for (numberOfLine = 0; numberOfLine < fieldWidth; ++numberOfLine) {

                for (numberOfTile = 0; numberOfTile < fieldLenght; ++numberOfTile) {

                    if (field[numberOfLine][numberOfTile] != 7) {
                        tile.setTextureRect(IntRect(field[numberOfLine][numberOfTile] * tileSize, 0, tileSize, tileSize));
                        tile.setPosition(numberOfTile * tileSize, numberOfLine * tileSize);
                        window.draw(tile);
                    }
                }
            }

            if (figureIsPlaced == true) {
                for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                    tileCoords[numberOfTile].x = 0;
                    tileCoords[numberOfTile].y = 0;
                }
            }

            window.display();
        }

        delay -= 0.03;

        figureIsPlaced = false;
        }

       
    return 0;
}
