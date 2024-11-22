#include "utilities.h"
#include "core.h"
#include "camera.h"
#include "graphic_render.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Super Mario Bros.");
    sf::Clock clock;

    Camera camera;
    Renderer renderer(window);

    sf::Texture texture;
    if (!texture.loadFromFile(TEX_DIRECTORY + "/brick.png"))
    {
        std::cerr << "File opening error : " << TEX_DIRECTORY + "/brick\n";
    }

    begin(window);
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        update(deltaTime);
        render(renderer);
        window.clear();
        window.setView(camera.GetView(window.getSize()));
        window.display();
    }

    return 0;
}
