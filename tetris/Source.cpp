#include <SFML/Graphics.hpp>

using namespace sf;

const int fieldLenght = 20, fieldWidth = 10;

int field[fieldLenght][fieldWidth];

int main() {

    RenderWindow window(VideoMode(320, 480), "Tetris");

    while (window.isOpen()) {

        window.setVerticalSyncEnabled(true);

        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();

        

        window.display();
    }

    return 0;
}
