#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    Game game("Assets/Environment/bg.png", "Assets/Adventurer/adventurer-Sheet.png");
    game.processer();
    return 0;
}