#include <SFML/Graphics.hpp>
#include "MenuState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Forest Survival Simulator");
    window.setFramerateLimit(60);

    MenuState menu(window);
    while (window.isOpen()) {
        menu.handleEvents();
        menu.update();
        window.clear();
        menu.render();
        window.display();
    }
    return 0;
}
