#include "window.h"

sf::CircleShape circle(2.0f, 360u);

void begin(const sf::Window &window)
{
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
    circle.setPosition((sf::Vector2f)window.getSize() / 2.0f);
    circle.setFillColor(sf::Color::Yellow);
}

void update(float deltaTime)
{
}

void render(sf::RenderWindow &window)
{
    window.draw(circle);
}