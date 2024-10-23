#include "Start.h"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super Mario Game");
    window.setFramerateLimit(60);

    // Create an instance of the Start class
    Start startScreen;

    // Main game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Close the window when the user clicks the close button
            }
            // Start the game when any key is pressed
            if (event.type == sf::Event::KeyPressed && !startScreen.isGameStarted()) {
                // Here you can switch to your main game logic
                // For example: change game state or load the first level
            }
        }

        // Clear the window before drawing
        window.clear();

        // Draw the start screen
        startScreen.draw(window);

        // Display the content of the window
        window.display();
    }

    return 0;
}
