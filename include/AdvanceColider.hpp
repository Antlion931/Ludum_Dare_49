#pragma once

#include <SFML/Graphics.hpp>

#include "Colider.hpp"

class AdvanceColider : public Colider
{
public:
    AdvanceColider(sf::Texture& texture, sf::Vector2f textureBodySize, sf::IntRect* textureRect = nullptr);
    AdvanceColider(sf::Texture& texture, sf::Vector2f textureBodySize, sf::Vector2f coliderBodySize, float x, float y, sf::IntRect* textureRect = nullptr);
    AdvanceColider(const AdvanceColider& p);
    AdvanceColider();
    
    void Draw(sf::RenderWindow* window);
    void setPosition(float x, float y);

private:
    sf::RectangleShape textureBody;
    sf::RectangleShape coliderBody;
    float coliderBodyX, coliderBodyY;
};