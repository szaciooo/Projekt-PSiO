#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window) : window(window) {
    backgroundTexture.loadFromFile("assets/backgrounds/menu_bg1.png");
    backgroundSprite.setTexture(backgroundTexture);

    sf::Texture temp;

    temp.loadFromFile("assets/ui/button_start.png");
    buttonTexturesIdle.push_back(temp);
    temp.loadFromFile("assets/ui/button_start_hover.png");
    buttonTexturesHover.push_back(temp);

    temp.loadFromFile("assets/ui/button_howtoplay.png");
    buttonTexturesIdle.push_back(temp);
    temp.loadFromFile("assets/ui/button_howtoplay_hover.png");
    buttonTexturesHover.push_back(temp);

    sf::Vector2f buttonSize(300.f, 100.f);
    float buttonX = (1536 - 300) / 2.f; // = 618
    std::vector<float> buttonYs = {580.f, 680.f};

    for (size_t i = 0; i < 2; ++i) {
        sf::RectangleShape button(buttonSize);
        button.setPosition(buttonX, buttonYs[i]);
        button.setTexture(&buttonTexturesIdle[i]);
        buttonShapes.push_back(button);
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
                // Start
            } else if (hoveredButton == 1) {
                // Jak grać
            }
        }
    }
}

void MenuState::update() {
    // animacje
}

void MenuState::render() {
    window.draw(backgroundSprite);
    for (const auto& button : buttonShapes) {
        window.draw(button);
    }
}

void MenuState::updateButtonStates() {
    hoveredButton = -1;
    for (size_t i = 0; i < buttonShapes.size(); ++i) {
        auto bounds = buttonShapes[i].getGlobalBounds();
        if (bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            buttonShapes[i].setTexture(&buttonTexturesHover[i]);
            hoveredButton = static_cast<int>(i);
        } else {
            buttonShapes[i].setTexture(&buttonTexturesIdle[i]);
        }
    }
}
