#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "Player.hpp"
#include "Animation.hpp"

Player::Player(sf::Texture* Idle_texture, unsigned int Idle_imageCount, float Idle_switchTime,
               sf::Texture* Run_texture, unsigned int Run_imageCount, float Run_switchTime,
               sf::Texture* Jump_texture, unsigned int Jump_imageCount, float Jump_switchTime, 
               float p_speed, float p_jumpHeight, sf::Vector2f bodyTextureSize, sf::Vector2f bodyColiderSize)
: Idle(Idle_texture, Idle_imageCount, Idle_switchTime), 
  Run(Run_texture, Run_imageCount, Run_switchTime), 
  Jump(Jump_texture, Jump_imageCount, Jump_switchTime), 
  speed(p_speed), jumpHeight(p_jumpHeight), faceRight(true), bodyTexture(bodyTextureSize), bodyColider(bodyColiderSize), animation(&Idle), 
  colider(&bodyColider), groundColider(&bodyGroundColider)
{
    canJump = false;
    bodyTexture.setPosition(300.0f, 300.0f);
    //std::cout << body.getOrigin().x << ", " << body.getOrigin().y << std::endl;
    bodyTexture.setOrigin(bodyTexture.getSize() / 2.0f);
    //std::cout << body.getOrigin().x << ", " << body.getOrigin().y << std::endl;
    bodyTexture.setTexture(animation -> texture);

    bodyColider.setOrigin(bodyColider.getSize() / 2.0f);
    bodyColider.setPosition(bodyTexture.getPosition()); 

    bodyGroundColider.setFillColor(sf::Color::Red);
    bodyGroundColider.setSize(sf::Vector2f(bodyColider.getSize().x * 0.95f, 40.0f));  
    bodyGroundColider.setOrigin(bodyGroundColider.getSize() / 2.0f);
    bodyGroundColider.setPosition(bodyColider.getPosition().x, bodyColider.getPosition().y + bodyColiderSize.x / 2.0f);
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

    if(!isOnGround)
    {
        velocity.y += 9.81f * 100.0f * deltaTime;
    }
    
    
    bodyColider.move(velocity * deltaTime);
    bodyGroundColider.setPosition(bodyColider.getPosition().x, bodyColider.getPosition().y + bodyColider.getSize().x / 2.0f);
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
    window -> draw(bodyTexture);

   //s window -> draw(bodyGroundColider);
}

void Player::SetPosition(float p_x, float p_y)
{
    bodyTexture.setPosition(p_x, p_y);
    bodyColider.setPosition(p_x, p_y);
    bodyGroundColider.setPosition(p_x, p_y + bodyColider.getSize(). y / 2.0f);
}


void Player::setIsOnGround(bool newValue)
{
    isOnGround = newValue;
    canJump = newValue;
}
