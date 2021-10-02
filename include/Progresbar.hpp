#pragma once

#include <SFML/Graphics.hpp>

class Progressbar
{
public:
    Progressbar(float p_x, float p_y);

    bool isFull();
    void changeProgress(float change);
    void Draw(sf::RenderWindow* window);

private:
    sf::RectangleShape bar;
    sf::RectangleShape background;
};