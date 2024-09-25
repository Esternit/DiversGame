#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    Game game("Assets/Environment/bg.png", "Assets/Adventurer/Individual Sprites/adventurer-idle-03.png");
    game.processer();
    return 0;
}