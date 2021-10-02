#include <SFML/Graphics.hpp>

#include "BloodBag.hpp"

BloodBag::BloodBag(sf::Texture* texture, sf::Vector2f size)
: Colider(&body)
{
    body.setSize(size);
    body.setTexture(texture);
    body.setOrigin(body.getSize() / 2.0f);
}

BloodBag::BloodBag(const BloodBag& bag)
: Colider(&body)
{
    body = bag.body;
}

void BloodBag::Draw(sf::RenderWindow* window)
{
    window -> draw(body);
}

void BloodBag::setPosition(float x, float y)
{
    body.setPosition(x, y);
}