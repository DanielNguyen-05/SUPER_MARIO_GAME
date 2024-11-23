#include "utilities.h"
#include "world_core.h"
#include "resource_manager.h"
#include <filesystem>

Camera camera(310.0f);

void begin(const sf::Window &window)
{
    for (auto &file : std::filesystem::directory_iterator(TEX_DIRECTORY))
    {
        if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
        {
            ResManager::textures[file.path().filename().string()].loadFromFile(
                file.path().string());
        }
    }
}

void update(float deltaTime)
{
}

void render(Renderer &renderer)
{
}
