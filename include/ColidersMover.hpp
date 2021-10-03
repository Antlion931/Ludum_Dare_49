#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Colider.hpp"

class ColidersMover
{
public:
    ColidersMover(float p_speed, sf::Vector2f p_begin, sf::Vector2f p_end);

    void add(Colider* colider);
    void Update(float deltaTime);

private:
    sf::Vector2f begin;
    sf::Vector2f end;

    std::vector<Colider*> coliders;

    float speed;
};