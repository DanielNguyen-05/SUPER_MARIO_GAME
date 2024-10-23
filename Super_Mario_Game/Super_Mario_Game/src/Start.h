#pragma once
#ifndef START_H
#define START_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Start {
    private:
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bool gameStarted;

    public:
        Start();
        void draw(sf::RenderWindow& window);
        bool isGameStarted() const;
};

#endif // START_H
