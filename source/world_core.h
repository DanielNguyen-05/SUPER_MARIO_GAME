#pragma once
#include <SFML/Graphics.hpp>
#include "camera.h"
#include "graphic_render.h"

extern Camera camera;

void begin(const sf::Window &window);
void update(float deltaTime);
void render(Renderer &renderer);
