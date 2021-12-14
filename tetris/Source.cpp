#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int fieldLenght = 20, fieldWidth = 10, tileSize = 18;

bool field[fieldLenght][fieldWidth];

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

int main() {

    srand(time(NULL));

    RenderWindow window(VideoMode(fieldWidth * tileSize, fieldLenght * tileSize), "Tetris");

    window.setVerticalSyncEnabled(true);

    Texture tTiles, tBackground;
    tTiles.loadFromFile("C:/Users/Анжелика/source/repos/Tetris/Tetris/images/tiles.png");
    tBackground.loadFromFile("C:/Users/Анжелика/source/repos/Tetris/Tetris/images/tiles.png");

    Sprite tile(tTiles), background(tBackground);

    int figureType, numberOfTile;

    while (window.isOpen()) {

        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }

        //figureType = rand() % 7;
        figureType = 2;
        for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

            tileCoords[numberOfTile].x = localTileCoords[figureType][numberOfTile] % 2;
            tileCoords[numberOfTile].y = localTileCoords[figureType][numberOfTile] / 2;
        }

        window.clear(Color::White);

        for (numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {
            tile.setTextureRect(IntRect(0, 0, tileSize, tileSize));
            tile.setPosition(tileCoords[numberOfTile].x + 10, tileCoords[numberOfTile].y + 10);
            window.draw(tile);
        }

        window.display();
    }

    return 0;
}
