#include "Minotaur.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Minotaur::Minotaur(const std::string& Path, float posX, float posY) : Enemy(Path, posX, posY, FrameAnimation(0, 50, 0, 40), 80,70) {

}

