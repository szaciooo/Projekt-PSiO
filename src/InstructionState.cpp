//InstructionState.cpp
#include "InstructionState.h"
#include <iostream> // tylko do debugowania, można usunąć

InstructionState::InstructionState(sf::RenderWindow& window) : window(window) {
    backgroundTexture.loadFromFile("assets/backgrounds/menu_bg1.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setColor(sf::Color(255, 255, 255, 150)); // lekki blur

    font.loadFromFile("assets/fonts/PixelFont.ttf");

    // Instrukcja gry
    instructions.setFont(font);
    instructions.setCharacterSize(32);
    instructions.setFillColor(sf::Color::White);
    instructions.setString(
        "STEROWANIE:\n"
        "WASD - sterowanie bohaterem\n"
        "I - ekwipunek\n"
        "SPACEBAR - atak"
        );

    sf::FloatRect bounds = instructions.getLocalBounds();
    instructions.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    instructions.setPosition(1536 / 2.f, 1024 / 2.f);

    // Tekst X
    xText.setFont(font);
    xText.setCharacterSize(32);
    xText.setString("X");
    xText.setFillColor(sf::Color::White);
    xText.setPosition(20.f, 20.f);

    // Ukryty hitbox
    xHitbox.setSize(sf::Vector2f(50.f, 50.f));
    xHitbox.setPosition(15.f, 15.f);
    xHitbox.setFillColor(sf::Color(255, 255, 255, 0)); // całkowicie przezroczysty
}

void InstructionState::handleEvents(bool& backToMenu) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseMoved) {
            updateHover();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            updateHover(); // upewnij się, że hover działa nawet bez ruchu myszy
            if (hovered) {
                //std::cout << "Klikniety X" << std::endl;
                backToMenu = true;
            }
        }
    }
}

void InstructionState::updateHover() {
    auto mousePos = sf::Mouse::getPosition(window);
    if (xHitbox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        hovered = true;
        xText.setFillColor(sf::Color::Yellow);
        std::cout << "HOVERED" << std::endl;
    } else {
        hovered = false;
        xText.setFillColor(sf::Color::White);
    }
}


void InstructionState::update() {
    // Brak dynamicznej logiki
}

void InstructionState::render() {
    window.draw(backgroundSprite);
    window.draw(instructions);
    window.draw(xText);
    // window.draw(xHitbox); // debug hitboxa
}
