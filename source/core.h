#pragma once
#include <SFML/Graphics.hpp>
#include "camera.h"
#include "graphic_render.h"

void begin(const sf::Window &window);
void update(float deltaTime);
void render(Renderer &renderer);
