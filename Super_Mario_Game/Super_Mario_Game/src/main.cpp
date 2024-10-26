#include "../Header/Start.h"
#include "../Header/Button.h"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super Mario Game");
    window.setFramerateLimit(60);

    // Create an instance of the Start class
    Start startScreen;
    Button myButton;


    // Main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                startScreen.handleMouseClick(window);
            }
        }

        // Clear the window
        window.clear();

        // Draw the start screen
        startScreen.render(&window);
        myButton.render(&window);


        // Display the window
        window.display();
    }

    return 0;
}
