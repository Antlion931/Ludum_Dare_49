#pragma once
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Colider.hpp"


class Player
{
public:
    Player(float p_speed, float p_jumpHeight, float p_invincibleTime, sf::Vector2f bodyTextureSize, sf::Vector2f bodyColiderSize);
    ~Player();

    void setIdle(sf::Texture* Idle_texture, unsigned int Idle_imageCount, float Idle_switchTime);        
    void setRun(sf::Texture* Run_texture, unsigned int Run_imageCount, float Run_switchTime);       
    void setJump(sf::Texture* Jump_texture, unsigned int Jump_imageCount, float Jump_switchTime);       
    void setIsOnGround(bool newValue);

    bool isInvincible();
    void setInvincible();

    void reset();

    void hitCeiling();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow* window, float deltaTime);
    void SetPosition(float p_x, float p_y);

    Colider colider;
    Colider groundColider;
    Colider ceilingColider;
private:
    sf::RectangleShape bodyTexture;
    sf::RectangleShape bodyColider;
    sf::RectangleShape bodyGroundColider;
    sf::RectangleShape bodyCeilingColider;
    Animation *animation;
    Animation Idle;
    Animation Run;
    Animation Jump;

    float speed;
    bool faceRight;

    sf::Vector2f velocity;
    bool canJump;
    bool isOnGround;
    float jumpHeight;

    float invincibleTime;
    float invincibleTimer;

};