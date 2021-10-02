#include <SFML/Graphics.hpp>

#include "VolumeBar.hpp"
#include "Progresbar.hpp"

VolumeBar::VolumeBar(float p_x, float p_y, sf::Color backgroundColor, sf::Color fillColor)
: Progressbar(p_x, p_y, backgroundColor, fillColor)
{}

void VolumeBar::Update(sf::RenderWindow* window, float* masterVolume)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f bodySize = getSize();
        sf::Vector2f bodyPosition = getPosition();

        // std::cout << "Mouse: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        // std::cout << "Body Size: " << bodySize.x << ", " << bodySize.y << std::endl;
        // std::cout << "Body Position: " << bodyPosition.x << ", " << bodyPosition.y << std::endl;
 
        if(mousePosition.x >= bodyPosition.x && 
           mousePosition.x <= bodyPosition.x + bodySize.x &&
           mousePosition.y >= bodyPosition.y && 
           mousePosition.y <= bodyPosition.y + bodySize.y)
        {
            float newMasterVolume = (mousePosition.x - bodyPosition.x) / bodySize.x;
            *masterVolume = newMasterVolume;
            setProgress(newMasterVolume);
        }
    }
}