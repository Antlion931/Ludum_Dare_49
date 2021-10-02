#include <SFML/Graphics.hpp>
#include <iostream>

#include "Colider.hpp"

Colider::Colider(sf::RectangleShape* p_body)
: body(p_body)
{
    // std::cout << "Colider: " << body;
    // std::cout << std::endl;
}

Colider::~Colider()
{

}

bool Colider::CheckColison(Colider& other, float push)
{
    sf::Vector2f otherPositon = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPositon = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    
    float deltaX = otherPositon.x - thisPositon.x;
    float deltaY = otherPositon.y - thisPositon.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if(intersectX > intersectY)
        {
            if(deltaX > 0.0f)
            {
                Move(intersectX * (1.0f - push), 0.0f);
                other.Move(-intersectX * push, 0.0f);
            }
            else
            {
                Move(-intersectX * (1.0f - push), 0.0f);
                other.Move(intersectX * push, 0.0f); 
            }
        }
        else
        {
            if(deltaY > 0.0f)
            {
                Move(0.0f, intersectY * (1.0f - push));
                other.Move(0.0f, -intersectY * push);
            }
            else
            {
                Move(0.0f, -intersectY * (1.0f - push));
                other.Move(0.0f, intersectY * push);
            }
        }

        return true;
    }

    return false;
}

void Colider::Move(float p_x, float p_y)
{
    body -> move(p_x, p_y);
}

sf::Vector2f Colider::GetPosition()
{
    return body -> getPosition();
}

sf::Vector2f Colider::GetHalfSize()
{
    return body -> getSize() / 2.0f;
}