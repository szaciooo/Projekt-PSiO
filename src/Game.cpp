#include "Game.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

Game::Game(sf::RenderWindow& window) : window(window), player() {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udało się załadować mapy!");
    }
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        (float)window.getSize().x / mapTexture.getSize().x,
        (float)window.getSize().y / mapTexture.getSize().y
        );

    if (!font.loadFromFile("assets/fonts/PixelFont.ttf")) {
        throw std::runtime_error("Nie udało się załadować czcionki!");
    }

    // End Text
    endText.setFont(font);
    endText.setCharacterSize(64);
    endText.setFillColor(sf::Color::White);
    endText.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - 100.f);

    // X powrót
    xText.setFont(font);
    xText.setCharacterSize(32);
    xText.setString("X");
    xText.setFillColor(sf::Color::White);
    xText.setPosition(20.f, 20.f);

    xHitbox.setSize({50.f, 50.f});
    xHitbox.setPosition(15.f, 15.f);
    xHitbox.setFillColor(sf::Color(255, 255, 255, 0)); // przezroczysty

    spawnWave();
    lastRegenTime.restart();
}

void Game::handleEvents(bool& backToMenu) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (state == Playing) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
                showStats = !showStats;
            }
        } else {
            if (event.type == sf::Event::MouseMoved) {
                updateXHover();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                updateXHover();
                if (xHovered) {
                    backToMenu = true;
                }
            }
        }
    }
}

void Game::update() {
    if (state != Playing) return;

    float deltaTime = clock.restart().asSeconds();
    player.update(deltaTime);

    for (auto& enemy : skeletons) {
        enemy.update(deltaTime, player.getPosition());
    }

    if (player.isAttacking()) {
        for (auto& enemy : skeletons) {
            if (player.getAttackBounds().intersects(enemy.getBounds())) {
                enemy.takeDamage(player.getAttackStrength());
            }
        }
    }

    for (auto& enemy : skeletons) {
        if (enemy.getBounds().intersects(player.getBounds()) && enemy.canAttack()) {
            player.takeDamage(enemy.getAttackStrength());
            enemy.resetAttackCooldown();
        }
    }

    skeletons.erase(std::remove_if(skeletons.begin(), skeletons.end(), [&](const SkeletonEnemy& e) {
                        if (e.getHealth() <= 0) {
                            player.heal(5.f);
                            return true;
                        }
                        return false;
                    }), skeletons.end());

    if (lastRegenTime.getElapsedTime().asSeconds() > 3.f) {
        player.heal(1.f);
        lastRegenTime.restart();
    }

    if (skeletons.empty()) {
        if (wave < 10) {
            wave++;
            spawnWave();
        } else {
            state = Won;
            endText.setString("WYGRANA");
        }
    }

    if (player.getHealth() <= 0 && state == Playing) {
        state = Lost;
        endText.setString("PRZEGRANA");
    }
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    for (auto& enemy : skeletons) {
        enemy.render(window);
        drawHealthBar(enemy.getPosition(), enemy.getHealth(), 100.f);
    }

    drawHealthBar(player.getPosition(), player.getHealth(), 100.f);
    drawUI();

    if (state == Won || state == Lost) {
        window.draw(endText);
        window.draw(xText);
        // window.draw(xHitbox); // Debug hitboxa
    }
}

void Game::spawnWave() {
    int count = 3 + wave;
    skeletons.clear();

    for (int i = 0; i < count; ++i) {
        sf::Vector2f pos(rand() % 1400 + 50, rand() % 900 + 50);
        skeletons.emplace_back(pos, wave * 0.8f + 2.f);
    }
}

void Game::drawUI() {
    if (state != Playing) return;

    sf::Text topLeft;
    topLeft.setFont(font);
    topLeft.setCharacterSize(28);
    topLeft.setFillColor(sf::Color::White);
    std::stringstream ss;
    ss << "Fala: " << wave << "/10 | Wrogowie: " << skeletons.size();
    topLeft.setString(ss.str());
    topLeft.setPosition(10, 10);
    window.draw(topLeft);

    if (showStats) {
        sf::Text stats;
        stats.setFont(font);
        stats.setCharacterSize(26);
        stats.setFillColor(sf::Color::White);
        std::stringstream ss2;
        ss2 << "Zdrowie: " << (int)player.getHealth() << "\n";
        ss2 << "Sila: " << (int)player.getAttackStrength() << "\n";
        ss2 << "Szybkosc: 100";
        stats.setString(ss2.str());

        float textWidth = stats.getLocalBounds().width;
        float x = window.getSize().x - textWidth - 20;
        stats.setPosition(x, 20);
        window.draw(stats);
    }
}

void Game::drawHealthBar(sf::Vector2f pos, float hp, float maxHp) {
    sf::RectangleShape bg(sf::Vector2f(40, 5));
    bg.setFillColor(sf::Color(50, 50, 50));
    bg.setPosition(pos.x + 12, pos.y - 10);

    sf::RectangleShape hpBar(sf::Vector2f(40 * (hp / maxHp), 5));
    hpBar.setFillColor(sf::Color::Green);
    hpBar.setPosition(pos.x + 12, pos.y - 10);

    window.draw(bg);
    window.draw(hpBar);
}

void Game::updateXHover() {
    auto mousePos = sf::Mouse::getPosition(window);
    if (xHitbox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        xHovered = true;
        xText.setFillColor(sf::Color::Yellow);
    } else {
        xHovered = false;
        xText.setFillColor(sf::Color::White);
    }
}
