#pragma once
#include <SFML/Graphics.hpp>

class Colider
{
public:
    Colider(sf::RectangleShape* p_body);
    ~Colider();

    bool CheckColison(Colider& other, float push);
    void Move(float p_x, float p_y);

    sf::Vector2f GetPosition();
    sf::Vector2f GetHalfSize();
private:
    sf::RectangleShape* body;

};
