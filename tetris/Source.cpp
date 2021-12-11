#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int field[10][20] = { 0 };

int figure[7][4] = {
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,3,5,7,
	3,5,7,6,
	2,3,4,5,
}

int main() {
	RenderWindow window(VideoMode(320, 480), "Tetris");

	Texture tFigure, tBackground;
	tFigure.loadFromFile("C:/Users/aveng/source/repos/tetris/images/tiles.png");
	tBackground.loadFromFile("C:/Users/aveng/source/repos/tetris/images/background.png");

	Sprite tiles(tFigure), background(tBackground);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear();
		window.draw();
		window.display();
	}
}
