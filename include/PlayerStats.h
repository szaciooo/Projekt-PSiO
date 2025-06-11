// PlayerStats.h
#pragma once
#include <SFML/Graphics.hpp>

class PlayerStats {
public:
    PlayerStats();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void nextWave();
    void heal(float amount);
    void takeDamage(float amount);
    void toggle();

    float getAttackStrength() const;
    float getSpeed() const;
    bool isDead() const;
    bool isVisible() const;

private:
    float health;
    float maxHealth;
    float strength;
    float speed;
    int wave;

    float regenRate;

    sf::Font font;
    sf::Text statsText;
    sf::RectangleShape background;
    bool showStats;

    void updateText();
};
