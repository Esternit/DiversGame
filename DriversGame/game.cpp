#include "game.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>

using namespace sf;

Game::Game(std::string BGpath) {
    Texture BackgorundPanel;
    BackgorundPanel.loadFromFile(BGpath);
    RectangleShape GameBackgorund(Vector2f(1280, 720));
    GameBackgorund.setTexture(&BackgorundPanel);
    GameBackgorund.setPosition(Vector2f(0, 0));
    std::cout << BGpath << std::endl;
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
        window.draw(GameBackgorund);
        window.display();
    }
}