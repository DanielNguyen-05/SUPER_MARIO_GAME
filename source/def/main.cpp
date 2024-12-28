#include "../header/DEFINITION.h"
#include "../header/MainMenu.h"
#include <fstream>
#include <iostream>

int main()
{
    system("cls");
    /*** Hides the console window when running the game ***/
    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Super Mario Game", sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(60); // Limit the framerate to 60 FPS.

    MainMenu *menu = MainMenu::getInstance();

    /*** Game Loop ***/
    while (window.isOpen())
    {
        sf::Event event;

        /*** Events Loop ***/
        while (window.pollEvent(event))
        {
            // Close the game when the window's close button is clicked
            if (event.type == sf::Event::Closed)
                window.close();

            menu->handleAllEvents(event);
        }

        // Clear the window
        window.clear();
        menu->drawAll(window);
        // Display the contents of the window
        window.display();
    }

    return 0;
}

/*
class Game
{
    Mario mario;
    std::vector<Entity> mobs;
    TileMap map;
    GameInfo gameInfo;
    Menu menu;

    sf::Event sfEvent;

    DWORD currentTickCount;
    DWORD lastDrawTickCount;

    SoundBuffer mushroomBuffer, stompBuffer;
    Sound mushroomSound, stompSound;

    bool won = false;

public:
    sf::RenderWindow *window;
    sf::View view;
    friend class Mario;
    // constructors/destructors
    Game();
    virtual ~Game();

    // functions
    void intersection(Mario &mario, Entity &entity);
    void updateSFMLEvents();
    void update();
    void render();
    void run();
    void Menu(int center);
    void cameraMovement();
    void repairSFMLTextures();
    void drawMobs();
    void Bonuses();
    void addMobs();
};
*/
