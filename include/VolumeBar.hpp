#pragma once

#include <SFML/Graphics.hpp>

#include "Progresbar.hpp"

class VolumeBar : public Progressbar
{
public:
    VolumeBar(float p_x, float p_y, sf::Color backgroundColor, sf::Color fillColor);

    void Update(sf::RenderWindow* window, float* masterVolume);
};