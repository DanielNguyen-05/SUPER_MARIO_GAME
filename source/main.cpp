#include <SFML/Graphics.hpp>
#include "window.h"
#include "camera.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Super Mario Bros.");
    sf::Clock clock;

    Camera camera(5.0f); // Zoom level mặc định

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

            // Xử lý sự kiện thay đổi kích thước cửa sổ
            if (event.type == sf::Event::Resized)
            {
                sf::Vector2u newSize(event.size.width, event.size.height);
                window.setView(camera.GetView(newSize)); // Cập nhật view
            }
        }

        // Áp dụng view từ camera
        window.setView(camera.GetView(window.getSize()));

        update(deltaTime);
        window.clear();
        render(window);
        window.display();
    }

    return 0;
}
