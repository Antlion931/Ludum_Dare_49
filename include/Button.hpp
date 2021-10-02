#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(sf::Texture* texture, sf::Vector2f size);
    Button(sf::Text* p_text, sf::Color fillColor, sf::Color outLineColor, sf::Vector2f size);

    bool isButtonPush(sf::RenderWindow* window);
    void Draw(sf::RenderWindow* window);
    void setPosition(float x, float y);
private:
    sf::RectangleShape body;
    sf::Text* text;
};