#include <SFML/Graphics.hpp>
#include <iostream>

#include "Progressbar.hpp"

Progressbar::Progressbar(float p_x, float p_y, sf::Color backgroundColor, sf::Color fillColor)
{
    background.setFillColor(backgroundColor);
    bar.setFillColor(fillColor);

    background.setSize(sf::Vector2f(p_x, p_y));
    bar.setSize(sf::Vector2f(0.0f, p_y));

    background.setPosition(0.0f, 0.0f);
    bar.setPosition(0.0f, 0.0f);
}

float Progressbar::getProgress()
{
    //std::cout << "get progress = " << bar.getSize().x / background.getSize().x << std::endl;
    return bar.getSize().x / background.getSize().x;
}

void Progressbar::setProgress(float newProgress)
{
    newProgress = std::min(std::max(newProgress, 0.0f), 1.0f);
    //std::cout << "set progress = " << newProgress << std::endl;

    bar.setSize(sf::Vector2f(background.getSize().x * newProgress, background.getSize().y));
}

void Progressbar::changeProgress(float change)
{
    float newProgress = getProgress() + change;
    //std::cout << "change progress = " << newProgress << std::endl;

    setProgress(newProgress);
}

void Progressbar::Draw(sf::RenderWindow* window)
{
    window -> draw(background);
    window -> draw(bar);
}

void Progressbar::setPosition(float x, float y)
{
    background.setPosition(x, y);
    bar.setPosition(x, y);
}

sf::Vector2f Progressbar::getPosition()
{
    return background.getPosition();
}

sf::Vector2f Progressbar::getSize()
{
    return background.getSize();
}
