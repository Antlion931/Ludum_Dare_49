#pragma once

#include <SFML/Graphics.hpp>

#include "Colider.hpp"

class AdvanceColider : public Colider
{
public:
    AdvanceColider(sf::Texture& texture, sf::Vector2f size, sf::IntRect* textureRect = nullptr);
    AdvanceColider(const AdvanceColider& p);
    AdvanceColider();
    
    void Draw(sf::RenderWindow* window);
    void setPosition(float x, float y);

private:
    sf::RectangleShape body;
};