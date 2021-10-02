#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.hpp"

Button::Button(sf::Texture* texture, sf::Vector2f size)
: text(NULL)
{
    body.setSize(size);
    body.setTexture(texture);
}

Button::Button(sf::Text* p_text, sf::Color fillColor, sf::Color outLineColor, sf::Vector2f size)
: text(p_text)
{
    body.setSize(size);
    body.setFillColor(fillColor);
    body.setOutlineColor(outLineColor);
    body.setOutlineThickness(20.0f);
}

bool Button::isButtonPush(sf::RenderWindow* window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f bodySize = body.getSize();
        sf::Vector2f bodyPosition = body.getPosition();

        // std::cout << "Mouse: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        // std::cout << "Body Size: " << bodySize.x << ", " << bodySize.y << std::endl;
        // std::cout << "Body Position: " << bodyPosition.x << ", " << bodyPosition.y << std::endl;
 
        if(mousePosition.x >= bodyPosition.x && 
           mousePosition.x <= bodyPosition.x + bodySize.x &&
           mousePosition.y >= bodyPosition.y && 
           mousePosition.y <= bodyPosition.y + bodySize.y)
        {
            return true;
        }
    }
    return false;
}

void Button::Draw(sf::RenderWindow* window)
{
    window -> draw(body);
    if(text)
    {
        window -> draw(*text);
    }
}

void Button::setPosition(float x, float y)
{
    body.setPosition(x, y);
}