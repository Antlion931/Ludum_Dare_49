#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.hpp"
#include "Animation.hpp"

Player::Player(sf::Texture* Idle_texture, unsigned int Idle_imageCount, float Idle_switchTime,
               sf::Texture* Run_texture, unsigned int Run_imageCount, float Run_switchTime,
               sf::Texture* Jump_texture, unsigned int Jump_imageCount, float Jump_switchTime, 
               float p_speed, sf::Vector2f bodyTextureSize, sf::Vector2f bodyColiderSize)
: Idle(Idle_texture, Idle_imageCount, Idle_switchTime), 
  Run(Run_texture, Run_imageCount, Run_switchTime), 
  Jump(Jump_texture, Jump_imageCount, Jump_switchTime), 
  speed(p_speed), faceRight(true), bodyTexture(bodyTextureSize), bodyColider(bodyColiderSize), animation(&Idle), colider(&bodyColider)
{
    bodyTexture.setPosition(300.0f, 300.0f);
    //std::cout << body.getOrigin().x << ", " << body.getOrigin().y << std::endl;
    bodyTexture.setOrigin(bodyTexture.getSize() / 2.0f);
    //std::cout << body.getOrigin().x << ", " << body.getOrigin().y << std::endl;
    bodyTexture.setTexture(animation -> texture);

    bodyColider.setOrigin(bodyColider.getSize() / 2.0f);
    bodyColider.setPosition(bodyTexture.getPosition());   
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movement.x -= speed * deltaTime;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movement.x += speed * deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movement.y -= speed * deltaTime;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movement.y += speed * deltaTime;
    }

    if(movement.x == 0.0f && movement.y == 0.0f)
    {
        animation = &Idle;
    }
    else
    {
        animation = &Run;

        if(movement.x > 0.0f)
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
    bodyColider.move(movement);
    bodyTexture.setPosition(bodyColider.getPosition());
}

void Player::Draw(sf::RenderWindow* window)
{
    window -> draw(bodyTexture);
}

void Player::SetPosition(float p_x, float p_y)
{
    bodyTexture.setPosition(p_x, p_y);
    bodyColider.setPosition(p_x, p_y);
}
