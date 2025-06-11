// Player.cpp
#include "Player.h"
#include <iostream>

Player::Player() {
    position = sf::Vector2f(700.f, 500.f);
    loadTextures();
    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
    weaponSprite.setTexture(weaponTexture);
    weaponSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Player::loadTextures() {
    if (!walkTexture.loadFromFile("assets/player/BODY_male_walk.png")) {
        std::cerr << "Failed to load walk texture!" << std::endl;
    }
    if (!hurtTexture.loadFromFile("assets/player/BODY_male_hurt.png")) {
        std::cerr << "Failed to load hurt texture!" << std::endl;
    }
    if (!bodyWeaponTexture.loadFromFile("assets/player/BODY_human.png")) {
        std::cerr << "Failed to load body weapon texture!" << std::endl;
    }
    if (!weaponTexture.loadFromFile("assets/player/WEAPON_dagger.png")) {
        std::cerr << "Failed to load weapon texture!" << std::endl;
    }
}

void Player::handleInput() {
    velocity = {0.f, 0.f};
    isMoving = false;
    isAttacking = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= speed;
        direction = Left;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += speed;
        direction = Up;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += speed;
        direction = Right;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y -= speed;
        direction = Down;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        isAttacking = true;
    }
}

void Player::update(float deltaTime) {
    handleInput();
    position += velocity * deltaTime;
    sprite.setPosition(position);
    weaponSprite.setPosition(position);
    updateAnimation();
}

void Player::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame = (currentFrame + 1) % 6;
        animationClock.restart();
    }

    int row = 0;
    switch (direction) {
    case Down:  row = 0; break;
    case Left:  row = 1; break;
    case Right: row = 2; break;
    case Up:    row = 3; break;
    }

    if (isAttacking) {
        sprite.setTexture(bodyWeaponTexture);
        weaponSprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
        sprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
    } else if (isMoving) {
        sprite.setTexture(walkTexture);
        sprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
    } else {
        sprite.setTexture(walkTexture);
        sprite.setTextureRect(sf::IntRect(0, row * 64, 64, 64));
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
    if (isAttacking) {
        window.draw(weaponSprite);
    }
}
