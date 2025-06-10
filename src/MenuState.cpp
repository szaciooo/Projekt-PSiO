#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window) : window(window) {
    font.loadFromFile("assets/fonts/OpenSans.ttf");

    titleText.setFont(font);
    titleText.setString("Forest Survival Simulator");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Green);
    titleText.setPosition(100, 50);

    std::vector<std::string> labels = {"Start", "Jak grać", "Wyniki"};
    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text button;
        button.setFont(font);
        button.setString(labels[i]);
        button.setCharacterSize(28);
        button.setFillColor(sf::Color::White);
        button.setPosition(100, 150 + static_cast<float>(i) * 60);
        buttons.push_back(button);
    }
}

void MenuState::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseMoved) {
            updateButtonStates();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (hoveredButton == 0) {
                // Start Game
            } else if (hoveredButton == 1) {
                // Show Instructions
            } else if (hoveredButton == 2) {
                // Show High Scores
            }
        }
    }
}

void MenuState::update() {
    // Tu można dodać animacje, efekty itp.
}

void MenuState::render() {
    window.draw(titleText);
    for (auto& button : buttons) {
        window.draw(button);
    }
}

void MenuState::updateButtonStates() {
    hoveredButton = -1;
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto bounds = buttons[i].getGlobalBounds();
        if (bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            buttons[i].setFillColor(sf::Color::Yellow);
            hoveredButton = static_cast<int>(i);
        } else {
            buttons[i].setFillColor(sf::Color::White);
        }
    }
}
