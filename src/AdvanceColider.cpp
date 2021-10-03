#include <SFML/Graphics.hpp>
#include <iostream>

#include "AdvanceColider.hpp"
#include "Colider.hpp"

AdvanceColider::AdvanceColider(sf::Texture& texture, sf::Vector2f size, sf::IntRect* textureRect)
: Colider(&body)
{
    body.setSize(size);
    body.setTexture(&texture);
    if(textureRect)
    {
        body.setTextureRect(*textureRect);
    }
    body.setOrigin(body.getSize() / 2.0f);
}

AdvanceColider::AdvanceColider(const AdvanceColider& p)
: Colider(&body)
{
    body = p.body;
}

AdvanceColider::AdvanceColider()
: Colider(&body)
{}

void AdvanceColider::Draw(sf::RenderWindow* window)
{
    window -> draw(body);
}

void AdvanceColider::setPosition(float x, float y)
{
    body.setPosition(x, y);
}
