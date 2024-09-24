#include "game.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace sf;

Game::Game(std::string BGpath) {
    //setting and loading background
    if (!backgroundTexture.loadFromFile(BGpath)) {
        std::cerr << "Failed to load background image!" << std::endl;
        return;
    }

    GameBackground.setTexture(&backgroundTexture);


    sf::Vector2u textureSize = backgroundTexture.getSize();
    GameBackground.setSize(sf::Vector2f(textureSize.x, textureSize.y));
}

void Game::processer() {
    RenderWindow window(VideoMode(1280, 720), "Divers");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(GameBackground);
        window.display();
    }
}