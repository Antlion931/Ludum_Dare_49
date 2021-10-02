#include <SFML/Graphics.hpp>

#include "Animation.hpp"

Animation::Animation(sf::Texture* p_texture, unsigned int p_imageCount, float p_switchTime)
: imageCount(p_imageCount), switchTime(p_switchTime), totalTime(0.0f), texture(p_texture), currentImage(0)
{
    

    uvRect.width  = p_texture -> getSize().x / static_cast<float>(imageCount);
    uvRect.height = p_texture -> getSize().y;

}
    
Animation::~Animation()
{

}

void Animation::Update(float deltaTime, bool faceRight)
{
    totalTime += deltaTime;

    if(totalTime > switchTime)
    {
        totalTime -= switchTime;
        currentImage++;
        currentImage %= imageCount;
    }

    uvRect.top = 0;
    
    if(faceRight)
    {
        uvRect.width = abs(uvRect.width);
        uvRect.left = currentImage * uvRect.width;
    }
    else
    {
        uvRect.left = (currentImage + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}