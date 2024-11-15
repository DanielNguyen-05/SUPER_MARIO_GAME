#include "../Header/Menu.h"

// Set Back Text Properties
void Menu::setBackText() {
    if (!this->font.loadFromFile(CAIRO_REGULAR)) {
        std::cerr << "Error loading font" << "\n";
    }
    this->backText.setFont(this->font);
    this->backText.setString("Press ESC to exit!");
    this->backText.setCharacterSize(30);
    this->backText.setFillColor(sf::Color::Black);
    this->backText.setPosition(1350.0, 855.0);
}

// Set Changing Option Sound Properties
void Menu::setChangeOptionSound() {
    if (!this->changingOptionBuffer.loadFromFile(CHANGING_OPTION_SOUND)) {
        std::cerr << "Error loading sound" << "\n";
    }
    // Create a sound source (changingOptionSound) and bind it to the buffer
    this->changingOptionSound.setBuffer(this->changingOptionBuffer);
    this->changingOptionSound.setVolume(50);
}

// Draw Menu Options
void Menu::draw(sf::RenderWindow& window) {
    if (this->display == true) {
        window.draw(this->backText);
        window.draw(this->backGroundSprite);
    }
}

// Control Menu events
void Menu::catchEvents(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            this->hide();
            changingOptionSound.play();
        }
    }
}

// Make Menu display
void Menu::show() {
    this->display = true;
}

// Close Menu
void Menu::hide() {
    this->display = false;
}