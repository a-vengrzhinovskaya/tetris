#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int fieldLenght = 20, fieldWidth = 10;

int field[fieldLenght][fieldWidth];

struct tilePosition {
    int x, y;
};

int localTileCoords[7][4] = {
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};

class Figure {

private:
    tilePosition tileCoords[4];
    int type, tiles[4];

public:
    Figure(int numberOfFigure) {
        type = numberOfFigure;
    }

    void figureBuild(tilePosition tileCoords[4]) {

        for (int numberOfTile = 0; numberOfTile < 4; ++numberOfTile) {

            tileCoords[numberOfTile].x = localTileCoords[type][numberOfTile] % 2;
            tileCoords[numberOfTile].y = localTileCoords[type][numberOfTile] / 2;

        }
    }
};

Figure I(0), S(1), Z(2), T(3), L(4), J(5), O(6);

int main() {

    srand(time(NULL));

    RenderWindow window(VideoMode(320, 480), "Tetris");

    window.setVerticalSyncEnabled(true);

    Texture tTiles, tBackground;
    tTiles.loadFromFile("C:/Users/aveng/source/repos/tetris/images/tiles.png");
    tBackground.loadFromFile("C:/Users/aveng/source/repos/tetris/images/background.png");

    Sprite tiles(tTiles), background(tBackground);

    int figureType;

    while (window.isOpen()) {

        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }

        figureType = rand() % 7;


        window.clear();

        

        window.display();
    }

    return 0;
}
