#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "Player.hpp"
#include "Animation.hpp"

Player::Player(float p_speed, float p_jumpHeight, float p_invincibleTime, sf::Vector2f bodyTextureSize, sf::Vector2f bodyColiderSize)
: speed(p_speed), jumpHeight(p_jumpHeight), invincibleTime(p_invincibleTime), faceRight(true), bodyTexture(bodyTextureSize), bodyColider(bodyColiderSize), animation(nullptr), 
  colider(&bodyColider), groundColider(&bodyGroundColider), ceilingColider(&bodyCeilingColider)
{
    invincibleTimer = 0.0f;
    canJump = false;
    bodyTexture.setPosition(300.0f, 300.0f);
    bodyTexture.setOrigin(bodyTexture.getSize() / 2.0f);

    bodyColider.setOrigin(bodyColider.getSize() / 2.0f);
    bodyColider.setPosition(bodyTexture.getPosition()); 

    bodyGroundColider.setFillColor(sf::Color::Red);
    bodyGroundColider.setSize(sf::Vector2f(bodyColider.getSize().x * 0.95f, 30.0f));  
    bodyGroundColider.setOrigin(bodyGroundColider.getSize() / 2.0f);
    bodyGroundColider.setPosition(bodyColider.getPosition().x, bodyColider.getPosition().y + bodyColiderSize.x / 2.0f);

    bodyCeilingColider.setFillColor(sf::Color::Blue);
    bodyCeilingColider.setSize(sf::Vector2f(bodyColider.getSize().x * 0.95f, 30.0f)); 
    bodyCeilingColider.setOrigin(bodyCeilingColider.getSize() / 2.0f);
    bodyCeilingColider.setPosition(bodyColider.getPosition().x, bodyColider.getPosition().y - bodyColiderSize.x / 2.0f);
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    velocity.x = 0.0f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
    {
        canJump = false;
        velocity.y  = -std::sqrt(2.0f * 9.81f * 100.0f * jumpHeight);
    }

    velocity.y += 9.81f * 100.0f * deltaTime;

    if(isOnGround && velocity.y > 0.0f)
    {
        velocity.y = 0.0f;
    }
    
    
    invincibleTimer = std::max(0.0f, invincibleTimer - deltaTime);

    //std::cout << velocity.y << std::endl;

    bodyColider.move(velocity * deltaTime);
    bodyGroundColider.setPosition(bodyColider.getPosition().x, bodyColider.getPosition().y + bodyColider.getSize().x / 2.0f);
    bodyCeilingColider.setPosition(bodyColider.getPosition().x, bodyColider.getPosition().y - bodyColider.getSize().x / 2.0f);
}

void Player::Draw(sf::RenderWindow* window, float deltaTime)
{
   // std::cout << velocity.y << std::endl;
    if(!isOnGround)
    {
        animation = &Jump;

        if(velocity.x > 0.0f)
        {
            faceRight = true;
        }
        else
        {
            faceRight = false;
        }
    }
    else if(velocity.x == 0.0f)
    {
        animation = &Idle;
    }
    else
    {
        animation = &Run;

        if(velocity.x > 0.0f)
        {
            faceRight = true;
        }
        else
        {
            faceRight = false;
        }
    }

    animation -> Update(deltaTime, faceRight);
    bodyTexture.setTexture(animation -> texture);
    bodyTexture.setTextureRect(animation -> uvRect);
    bodyTexture.setPosition(bodyColider.getPosition());

    if(int(invincibleTimer * 10) % 3 != 1)
    {
        window -> draw(bodyTexture);
    }

//     window -> draw(bodyGroundColider);
//     window -> draw(bodyCeilingColider);
}

void Player::SetPosition(float p_x, float p_y)
{
    bodyTexture.setPosition(p_x, p_y);
    bodyColider.setPosition(p_x, p_y);
    bodyGroundColider.setPosition(p_x, p_y + bodyColider.getSize(). y / 2.0f);
    bodyGroundColider.setPosition(p_x, p_y - bodyColider.getSize(). y / 2.0f);
}

void Player::setIsOnGround(bool newValue)
{
    isOnGround = newValue;
    canJump = newValue;
}

void Player::setIdle(sf::Texture* Idle_texture, unsigned int Idle_imageCount, float Idle_switchTime)
{
    Idle = Animation(Idle_texture, Idle_imageCount, Idle_switchTime);
}   

void Player::setRun(sf::Texture* Run_texture, unsigned int Run_imageCount, float Run_switchTime)
{
    Run =  Animation(Run_texture, Run_imageCount, Run_switchTime);
}   

void Player::setJump(sf::Texture* Jump_texture, unsigned int Jump_imageCount, float Jump_switchTime)
{
    Jump = Animation(Jump_texture, Jump_imageCount, Jump_switchTime);
}

bool Player::isInvincible()
{
    if(invincibleTimer > 0.0f)
    {
        return true;
    }
    return false;
}

void Player::setInvincible()
{
    invincibleTimer = invincibleTime;
}

void Player::reset()
{
    isOnGround = false;
    invincibleTimer = 0.0f;
    canJump = false;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
}

void Player::hitCeiling()
{
    if(velocity.y < 0.0f)
    {
        velocity.y = 0.0f;
    }
}
