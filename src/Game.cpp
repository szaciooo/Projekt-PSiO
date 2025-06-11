// Game.cpp
#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) : window(window) {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udalo sie zaladowac mapy: assets/maps/forest_map.png");
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
    float deltaTime = clock.restart().asSeconds();
    player.update(deltaTime);
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);
}
