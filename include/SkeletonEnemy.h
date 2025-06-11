#pragma once
#include <SFML/Graphics.hpp>

class SkeletonEnemy {
public:
    SkeletonEnemy(sf::Vector2f spawnPos);

    void loadTextures();
    void update(float deltaTime, sf::Vector2f playerPos);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool isAlive() const;
    void takeDamage();

private:
    sf::Vector2f position;
    float speed = 100.f;
    bool alive = true;
    int health = 3;

    sf::Texture walkTexture;
    sf::Texture hurtTexture;
    sf::Texture deathTexture;
    sf::Sprite sprite;

    int currentFrame = 0;
    float frameDuration = 0.2f;
    sf::Clock animClock;

    void updateAnimation();
};
