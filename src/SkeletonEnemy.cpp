#include "SkeletonEnemy.h"
#include <iostream>
#include <cmath>

SkeletonEnemy::SkeletonEnemy(sf::Vector2f spawnPos) : position(spawnPos) {
    loadTextures();
    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void SkeletonEnemy::loadTextures() {
    if (!walkTexture.loadFromFile("assets/enemies/skeleton/BODY_skeleton.png")) {
        std::cerr << "Failed to load walk texture!" << std::endl;
    }
    if (!hurtTexture.loadFromFile("assets/enemies/skeleton/BODY_skeleton_hurt.png")) {
        std::cerr << "Failed to load hurt texture!" << std::endl;
    }
    if (!deathTexture.loadFromFile("assets/enemies/skeleton/BODY_skeleton_dead.png")) {
        std::cerr << "Failed to load death texture!" << std::endl;
    }
}

void SkeletonEnemy::update(float deltaTime, sf::Vector2f playerPos) {
    if (!alive) return;

    sf::Vector2f direction = playerPos - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    position += direction * speed * deltaTime;
    sprite.setPosition(position);
    updateAnimation();
}

void SkeletonEnemy::updateAnimation() {
    if (animClock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame = (currentFrame + 1) % 4;
        animClock.restart();
    }
    sprite.setTextureRect(sf::IntRect(currentFrame * 64, 0, 64, 64));
}

void SkeletonEnemy::render(sf::RenderWindow& window) {
    if (alive) {
        sprite.setTexture(walkTexture);
    } else {
        sprite.setTexture(deathTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    }
    window.draw(sprite);
}

sf::FloatRect SkeletonEnemy::getBounds() const {
    return sprite.getGlobalBounds();
}

bool SkeletonEnemy::isAlive() const {
    return alive;
}

void SkeletonEnemy::takeDamage() {
    health--;
    if (health <= 0) {
        alive = false;
    } else {
        sprite.setTexture(hurtTexture);
        animClock.restart();
    }
}
