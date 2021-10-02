#include <SFML/Graphics.hpp>
#include <iostream>

#include "Platform.hpp"
#include "Colider.hpp"

Platform::Platform(sf::Texture& texture, sf::IntRect& textureRect, sf::Vector2f size)
: Colider(&body)
{
    body.setSize(size);
    body.setTexture(&texture);
    body.setTextureRect(textureRect);
    body.setOrigin(body.getSize() / 2.0f);
}


Platform::Platform(const Platform& p)
: Colider(&body)
{
    body = p.body;
    //std::cout << "PLatform: " << &body << std::endl;
}

void Platform::Draw(sf::RenderWindow* window)
{
    window -> draw(body);
}

void Platform::setPosition(float x, float y)
{
    body.setPosition(x, y);
}
