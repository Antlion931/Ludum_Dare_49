#pragma once

#include <SFML/Graphics.hpp>

#include "Colider.hpp"

class Platform : public Colider
{
public:
    Platform(sf::Texture& texture, sf::IntRect& textureRect, sf::Vector2f size);
    Platform(const Platform& p);

    
    void Draw(sf::RenderWindow* window);
    void setPosition(float x, float y);

private:
    sf::RectangleShape body;
};