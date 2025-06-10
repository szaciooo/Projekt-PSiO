#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class MenuState {
public:
    MenuState(sf::RenderWindow& window);
    void handleEvents();
    void update();
    void render();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    std::vector<sf::Text> buttons; // "Start", "Jak grać", "Wyniki"

    int hoveredButton = -1;
    void updateButtonStates();
};
