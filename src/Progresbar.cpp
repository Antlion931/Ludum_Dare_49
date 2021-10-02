#include <SFML/Graphics.hpp>

#include "Progresbar.hpp"

Progressbar::Progressbar(float p_x, float p_y)
{
    background.setFillColor(sf::Color::Red);
    bar.setFillColor(sf::Color::Green);

    background.setSize(sf::Vector2f(1000.0f, 30.0f));
    bar.setSize(sf::Vector2f(0.0f, 30.0f));

    background.setPosition(p_x, p_y);
    bar.setPosition(p_x, p_y);
}

bool Progressbar::isFull()
{
    if(bar.getSize().x == background.getSize().x)
    {
        return true;
    }

    return false;
}

void Progressbar::changeProgress(float change)
{
    float newX = bar.getSize().x + change;

    if(newX > background.getSize().x)
    {
        newX = background.getSize().x;
    }
    else if(newX < 0.0f)
    {
        newX = 0.0f;
    }

    bar.setSize(sf::Vector2f(newX, bar.getSize().y));
}

void Progressbar::Draw(sf::RenderWindow* window)
{
    window -> draw(background);
    window -> draw(bar);
}
