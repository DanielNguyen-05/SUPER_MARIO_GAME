#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/textures/sky.png"))
    {
        return -1;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(
        static_cast<float>(WINDOW_WIDTH) / backgroundTexture.getSize().x,
        static_cast<float>(WINDOW_HEIGHT) / backgroundTexture.getSize().y);

    sf::Texture marioTexture;
    if (!marioTexture.loadFromFile("assets/textures/mario.png"))
    {
        return -1;
    }
    sf::Sprite mario(marioTexture);

    const int FRAME_WIDTH = 32;
    const int FRAME_HEIGHT = 32;

    mario.setTextureRect(sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
    mario.setPosition(100.f, 450.f);

    sf::Vector2f marioVelocity(0.f, 0.f);
    const float marioSpeed = 5.f;
    const float gravity = 0.5f;
    const float jumpVelocity = -10.f;
    bool isJumping = false;

    sf::RectangleShape ground(sf::Vector2f(WINDOW_WIDTH, 50.f));
    ground.setFillColor(sf::Color(139, 69, 19));
    ground.setPosition(0.f, 550.f);

    sf::RectangleShape platform1(sf::Vector2f(200.f, 20.f));
    platform1.setFillColor(sf::Color::Blue);
    platform1.setPosition(300.f, 400.f);

    sf::RectangleShape platform2(sf::Vector2f(150.f, 20.f));
    platform2.setFillColor(sf::Color::Blue);
    platform2.setPosition(550.f, 300.f);

    int currentFrame = 0;
    sf::Clock animationClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        marioVelocity.x = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            marioVelocity.x = -marioSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            marioVelocity.x = marioSpeed;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !isJumping)
        {
            marioVelocity.y = jumpVelocity;
            isJumping = true;
        }

        marioVelocity.y += gravity;

        mario.move(marioVelocity);

        if (mario.getGlobalBounds().intersects(ground.getGlobalBounds()))
        {
            mario.setPosition(mario.getPosition().x, ground.getPosition().y - FRAME_HEIGHT);
            marioVelocity.y = 0.f;
            isJumping = false;
        }
        else if (mario.getGlobalBounds().intersects(platform1.getGlobalBounds()))
        {
            mario.setPosition(mario.getPosition().x, platform1.getPosition().y - FRAME_HEIGHT);
            marioVelocity.y = 0.f;
            isJumping = false;
        }
        else if (mario.getGlobalBounds().intersects(platform2.getGlobalBounds()))
        {
            mario.setPosition(mario.getPosition().x, platform2.getPosition().y - FRAME_HEIGHT);
            marioVelocity.y = 0.f;
            isJumping = false;
        }

        if (animationClock.getElapsedTime().asSeconds() > 0.1f)
        {
            if (marioVelocity.x != 0)
            {
                currentFrame = (currentFrame + 1) % 3;
                mario.setTextureRect(sf::IntRect(currentFrame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT));
            }
            animationClock.restart();
        }

        window.clear();
        window.draw(background);
        window.draw(ground);
        window.draw(platform1);
        window.draw(platform2);
        window.draw(mario);
        window.display();
    }

    return 0;
}
