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

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    std::vector<sf::RectangleShape> buttonShapes;
    std::vector<sf::Texture> buttonTexturesIdle;
    std::vector<sf::Texture> buttonTexturesHover;

    int hoveredButton = -1;
    void updateButtonStates();
};
