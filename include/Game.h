#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "SkeletonEnemy.h"

class Game {
public:
    Game(sf::RenderWindow& window);

    void handleEvents(bool& backToMenu);
    void update();
    void render();

private:
    sf::RenderWindow& window;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::Clock clock;
    sf::Font font;

    Player player;
    std::vector<SkeletonEnemy> skeletons;

    int wave = 1;
    sf::Clock lastRegenTime;
    bool showStats = false;

    enum GameState { Playing, Won, Lost } state = Playing;

    sf::Text endText;
    sf::Text xText;
    sf::RectangleShape xHitbox;
    bool xHovered = false;

    void spawnWave();
    void drawUI();
    void drawHealthBar(sf::Vector2f pos, float hp, float maxHp);
    void updateXHover();
};
