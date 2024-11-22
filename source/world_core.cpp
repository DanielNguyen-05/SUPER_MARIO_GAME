#include "utilities.h"
#include "world_core.h"
#include "camera.h"
#include "graphic_render.h"

sf::Texture texture;

void begin(const sf::Window &window)
{
    if (!texture.loadFromFile(TEX_DIRECTORY + "/brick.png"))
    {
        exit(-1);
    }
}

void update(float deltaTime)
{
}

void render(Renderer &renderer)
{
    renderer.Draw(texture, sf::Vector2f(), sf::Vector2f(4.5f, 4.5f));
}
