#include "utilities.h"
#include "world_core.h"
#include "camera.h"
#include "graphic_render.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Super Mario Bros.");
    sf::Clock clock;

    Camera camera;
    Renderer renderer(window);

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
        window.clear();
        window.setView(camera.GetView(window.getSize()));
        render(renderer);
        window.display();
    }

    return 0;
}