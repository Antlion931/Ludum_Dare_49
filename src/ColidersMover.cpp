#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "ColidersMover.hpp"
#include "Colider.hpp"

ColidersMover::ColidersMover(float p_speed, sf::Vector2f p_begin, sf::Vector2f p_end)
: speed(p_speed), begin(p_begin), end(p_end)
{}

void ColidersMover::add(Colider* colider)
{
    coliders.push_back(colider);
}

void ColidersMover::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if(begin.x < end.x)
    {
        movement.x = speed * deltaTime;
    }
    else if( begin.x > end.x)
    {
        movement.x = -speed * deltaTime;
    }
    else if(begin.y < end.y)
    {
        movement.y = speed * deltaTime;
    }
    else if(begin.y > end.y)
    {
        movement.y = -speed * deltaTime;
    }

    float distanceFromBeginToEnd = std::sqrt( std::pow( begin.x - end.x, 2) + std::pow(begin.y - end.y, 2));

    for(Colider* c : coliders)
    {
        c -> Move(movement.x, movement.y);
        
        float distanceFromBeginToColider = std::sqrt( std::pow( begin.x - c -> GetPosition().x, 2) + std::pow(begin.y - c -> GetPosition().y, 2));
        if(distanceFromBeginToColider >= distanceFromBeginToEnd)
        {
            
            sf::Vector2f bufor = begin;
            begin = end;
            end = bufor;
        }
    
    }

}
