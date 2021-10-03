#include <SFML/Graphics.hpp>
#include <iostream>

#include "AdvanceColider.hpp"
#include "Colider.hpp"

AdvanceColider::AdvanceColider(sf::Texture& texture, sf::Vector2f textureBodySize, sf::IntRect* textureRect)
: Colider(&coliderBody)
{
    textureBody.setSize(textureBodySize);
    textureBody.setTexture(&texture);
    if(textureRect)
    {
        textureBody.setTextureRect(*textureRect);
    }
    textureBody.setOrigin(textureBody.getSize() / 2.0f);

    coliderBody = textureBody;
    coliderBodyX = 0.0f;
    coliderBodyY = 0.0f;
}


AdvanceColider::AdvanceColider(sf::Texture& texture, sf::Vector2f textureBodySize, sf::Vector2f coliderBodSize, float x, float y, sf::IntRect* textureRect)
: Colider(&coliderBody)
{
    textureBody.setSize(textureBodySize);
    textureBody.setTexture(&texture);
    if(textureRect)
    {
        textureBody.setTextureRect(*textureRect);
    }
    textureBody.setOrigin(textureBody.getSize() / 2.0f);

    coliderBody.setSize(coliderBodSize);
    coliderBody.setFillColor(sf::Color::Yellow);
    coliderBody.setOrigin(coliderBody.getSize() / 2.0f);
    coliderBodyX = x;
    coliderBodyY = y;
}

AdvanceColider::AdvanceColider(const AdvanceColider& p)
: Colider(&coliderBody)
{
    textureBody = p.textureBody;
    coliderBody = p.coliderBody;
    coliderBodyX = p.coliderBodyX;
    coliderBodyY = p.coliderBodyY;
}

AdvanceColider::AdvanceColider()
: Colider(&textureBody)
{}

void AdvanceColider::Draw(sf::RenderWindow* window)
{
    textureBody.setPosition(coliderBody.getPosition().x - coliderBodyX, coliderBody.getPosition().y - coliderBodyY);
    window -> draw(textureBody);
}

void AdvanceColider::setPosition(float x, float y)
{
    textureBody.setPosition(x, y);
    coliderBody.setPosition(x + coliderBodyX, y + coliderBodyY);
}
