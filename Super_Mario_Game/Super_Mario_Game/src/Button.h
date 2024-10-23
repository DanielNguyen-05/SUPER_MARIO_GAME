#pragma once
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace std;

class Button {
    private:
        sf::RectangleShape shape;
        sf::Text text;
        sf::Font* font;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        bool isButtonPressed;

    public:
        Button();
        Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
        ~Button();


        void render(sf::RenderTarget* target);
        bool isMouseOver(sf::RenderWindow& window) const;
        void update(const sf::Vector2f mousePos, sf::RenderWindow& window);

        sf::Font getFont() const { return *font; };
        const bool isPressed() const;

        // Getter and setter for button state
        void setPressed(bool pressed);
        bool getPressed() const;
};