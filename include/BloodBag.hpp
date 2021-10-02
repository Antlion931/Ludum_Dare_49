#pragma once
#include <SFML/Graphics.hpp>

#include "Colider.hpp"

class BloodBag : public Colider
{
public:
    BloodBag(sf::Texture* texture, sf::Vector2f size);
    BloodBag(const BloodBag& bag);

    void Draw(sf::RenderWindow* window);
    void setPosition(float x, float y);

private:
    sf::RectangleShape body;
};