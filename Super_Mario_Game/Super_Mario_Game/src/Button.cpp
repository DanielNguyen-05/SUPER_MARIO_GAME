#include "Button.h"

// Default constructor
Button::Button() {
    this->shape.setSize(sf::Vector2f(0, 0));
    this->shape.setFillColor(sf::Color::White);
    this->isButtonPressed = false;
}

Button::Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {
    // Set button shape
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(24);
    this->text.setPosition(
        x + (width - this->text.getGlobalBounds().width) / 2,
        y + (height - this->text.getGlobalBounds().height) / 2
    ); // Center text within the button

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
    this->isButtonPressed = false;  // Button is not pressed initially
}

// Check if the mouse is over the button
bool Button::isMouseOver(sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = shape.getGlobalBounds();
    return buttonBounds.contains(static_cast<sf::Vector2f>(mousePos));
}

// Update button state based on mouse position and clicks
void Button::update(const sf::Vector2f mousePos, sf::RenderWindow& window) {
    // Change button color based on mouse position
    if (shape.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shape.setFillColor(activeColor);
            this->isButtonPressed = true;
        } else {
            shape.setFillColor(hoverColor);
            this->isButtonPressed = false;
        }
    } else {
        shape.setFillColor(idleColor);
        this->isButtonPressed = false;
    }
}

// Render the button
void Button::render(sf::RenderTarget* target) {
    target->draw(shape);
    target->draw(text);
}

// Check if the button is pressed
const bool Button::isPressed() const {
    return isButtonPressed;
}

// Setter and getter for button state
void Button::setPressed(bool pressed) {
    this->isButtonPressed = pressed;
}

bool Button::getPressed() const {
    return this->isButtonPressed;
}

Button::~Button() {}
