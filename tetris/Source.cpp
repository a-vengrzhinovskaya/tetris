#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int field[10][20] = { 0 };

struct tilePosition {
	int x, y;
};

tilePosition a[4], b[4];

int figure[7][4] = {
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,3,5,7,
	3,5,7,6,
	2,3,4,5,
};

int main() {

	int currentFigure;

	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "Tetris");

	Texture tTiles, tBackground;
	tTiles.loadFromFile("C:/Users/aveng/source/repos/tetris/images/tiles.png");
	tBackground.loadFromFile("C:/Users/aveng/source/repos/tetris/images/background.png");

	Sprite tiles(tTiles), background(tBackground);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		currentFigure = 6;
		for (int tileNumber = 0; tileNumber < 4; ++tileNumber) {
			a[tileNumber].x = figure[currentFigure][tileNumber] % 2;
			a[tileNumber].y = figure[currentFigure][tileNumber] / 2;
		}

		window.clear();
		window.draw(background);
		for (int tileNumber = 0; tileNumber < 4; ++tileNumber) {
			tiles.setPosition(a[tileNumber].x * 18, a[tileNumber].y * 18);
			window.draw(tiles);
		}
		window.display();
	}
}
