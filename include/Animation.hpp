#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(sf::Texture* p_texture, unsigned int p_imageCount, float p_switchTime);
    ~Animation();

    sf::IntRect uvRect;
    sf::Texture *texture;

    void Update(float deltaTime, bool faceRight);

private:
    unsigned int imageCount;
    unsigned int currentImage;

    float totalTime;
    float switchTime;
};
