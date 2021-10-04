#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class SaveManager
{
public:
    float getHpFromLevel(unsigned int level);
    void addHpToLevel(unsigned int level, float hp);
    long int getScore();
};
