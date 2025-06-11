// Player.h
#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void loadTextures();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void handleInput();

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed = 200.f;

    sf::Texture walkTexture;
    sf::Texture hurtTexture;
    sf::Texture bodyWeaponTexture;
    sf::Texture weaponTexture;

    sf::Sprite sprite;
    sf::Sprite weaponSprite; //
    sf::Clock animationClock;
    int currentFrame = 0;
    float frameDuration = 0.15f;

    enum Direction { Down, Left, Right, Up } direction = Down;
    bool isMoving = false;
    bool isAttacking = false;

    void updateAnimation();

};
