#include "camera.h"

Camera::Camera(float level) : zoomLevel(level) {}

sf::View Camera::GetView(sf::Vector2u windowSize)
{
    float aspect = (float)windowSize.x / (float)windowSize.y;
    sf::Vector2f size;
    if (aspect < 1.0f)
    {
        size = sf::Vector2f(zoomLevel, zoomLevel / aspect);
    }
    else
    {
        size = sf::Vector2f(zoomLevel * aspect, zoomLevel);
    }
    sf::Vector2f center(windowSize.x / 2.0f, windowSize.y / 2.0f);
    return sf::View(center, size);
}