#include "Game.h"
#include <stdexcept>

Game::Game(sf::RenderWindow& window) : window(window) {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udało się załadować mapy: assets/maps/forest_map.png");
    }
    mapSprite.setTexture(mapTexture);
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
    // logika gry będzie tu
}

void Game::render() {
    window.draw(mapSprite);
}
