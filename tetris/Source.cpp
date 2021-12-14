#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int fieldLenght = 20, fieldWidth = 10, tileSize = 18;

bool field[fieldLenght][fieldWidth] = {false};

struct tilePosition {
    int x, y;
} tileCoords[4];

int localTileCoords[7][4] = {
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};

/*void rotation(int figureType, int* rotationState, tilePosition[4]) {
    switch (figureType) {
        case 0: {
            switch (*rotationState) {
                case 0: {

                }
            }
        }
    }
}*/

int main() {

    srand(time(NULL));

    RenderWindow window(VideoMode(fieldWidth * tileSize, fieldLenght * tileSize), "Tetris");

    window.setVerticalSyncEnabled(true);

    Texture tTiles, tBackground;
    tTiles.loadFromFile("C:/Users/Анжелика/source/repos/Tetris/Tetris/images/tiles.png");
    tBackground.loadFromFile("C:/Users/Анжелика/source/repos/Tetris/Tetris/images/tiles.png");

    Sprite tile(tTiles), background(tBackground);

    int figureType, numberOfTile, direction = 0;

    while (window.isOpen()) {

        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                /*if (event.key.code == Keyboard::Up) {
                    rotation();
                }*/
                if (event.key.code == Keyboard::Right) {
                    direction = 1;
                }
                else if (event.key.code == Keyboard::Left) {
                    direction = -1;
                }
            }
        }

        if (tileCoords[0].y == 0) {

            figureType = rand() % 7;

            for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

                tileCoords[numberOfTile].x = localTileCoords[figureType][numberOfTile] % 2;
                tileCoords[numberOfTile].y = localTileCoords[figureType][numberOfTile] / 2;
            }
        }

        for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

            tileCoords[numberOfTile].x += direction;
        }

        direction = 0;

        window.clear(Color::White);

        for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {
            tile.setTextureRect(IntRect(figureType * tileSize, 0, tileSize, tileSize));
            tile.setPosition(tileCoords[numberOfTile].x * tileSize, tileCoords[numberOfTile].y * tileSize);
            window.draw(tile);
        }

        window.display();
    }

    return 0;
}
