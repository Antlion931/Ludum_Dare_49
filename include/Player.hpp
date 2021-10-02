#pragma once
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Colider.hpp"


class Player
{
public:
    Player(sf::Texture* Idle_texture, unsigned int Idle_imageCount, float Idle_switchTime,
           sf::Texture* Run_texture, unsigned int Run_imageCount, float Run_switchTime,
           sf::Texture* Jump_texture, unsigned int Jump_imageCount, float Jump_switchTime, 
           float p_speed, sf::Vector2f bodyTextureSize, sf::Vector2f bodyColiderSize);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow* window);
    void SetPosition(float p_x, float p_y);

    Colider colider;
private:
    sf::RectangleShape bodyTexture;
    sf::RectangleShape bodyColider;
    Animation *animation;
    Animation Idle;
    Animation Run;
    Animation Jump;

    float speed;
    bool faceRight;
};