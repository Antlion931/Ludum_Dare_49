#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Button.hpp"
#include "Player.hpp"
#include "Colider.hpp"
#include "Animation.hpp"
#include "Progresbar.hpp"
#include "Platform.hpp"

enum screen
{
    START,
    SETTINGS,
    LEVEL1
};

int main()
{
    //WINDOW
    sf::RenderWindow window(sf::VideoMode(1280, 720), "The Game", sf::Style::Close | sf::Style::Titlebar);

    //MUSIC
    sf::Music mainTheme;
    mainTheme.openFromFile("res/Heart monitor remix.wav");
    mainTheme.setLoop(true);
    mainTheme.play();

    //FONT
    sf::Font font;
    font.loadFromFile("res/pixel-combat-font/PixelCombat-Wajz.ttf");

    //TERRAIN TEXTURE
    sf::Texture terrain;
    terrain.loadFromFile("res/Free/Terrain/Terrain (16x16).png");

    //PLAYER
    sf::Texture playerIdleTexture, playerRunTexture, playerJumpTexture;

    playerIdleTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Idle (32x32).png");
    playerRunTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Run (32x32).png");
    playerJumpTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Jump (32x32).png");

    Player player(&playerIdleTexture, 11, 0.1f, &playerRunTexture, 12, 0.05f, &playerJumpTexture, 1, 10.0f, 150.0f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(66.0f, 94.0f));

    //FILE STREAM
    std::ifstream f_input;
    float x, y;

    //PROGRESBAR
    Progressbar hp(10.0f, 10.0f);

//======================================================================================================================
    //START
        //PLAY BUTTON
        sf::Text playButtonText;
        playButtonText.setFont(font);
        playButtonText.setCharacterSize(150);
        playButtonText.setPosition(410.0f, 110.0f);
        playButtonText.setString("PLAY");

        Button playButton(&playButtonText, sf::Color::Black, sf::Color::White, sf::Vector2f(500.0f, 200.0f));
        playButton.setPosition(390.0f, 100.0f);

        //SETTINGS BUTTON
        sf::Texture settingsButtonTexture;
        settingsButtonTexture.loadFromFile("res/Free/Menu/Buttons/Settings.png");
        
        Button settingsButton(&settingsButtonTexture, sf::Vector2f(100.0f, 100.0f));
        settingsButton.setPosition(50.0f, 570.0f);

    //SETTINGS
        //TODO: VOLUME SETTINGS

    //1 LEVEL
        sf::IntRect level1_textureRect;
        level1_textureRect.height = 16;
        level1_textureRect.width = 16;
        level1_textureRect.left = 0;
        level1_textureRect.top = 0;

        Platform level1_platform(terrain,level1_textureRect, sf::Vector2f(50.0f, 50.0f));
        std::vector<Platform> level1_platforms;

        f_input.open("bin/levels/1.txt");
        while (f_input >> x >> y)
        {
            level1_platform.setPosition(x, y);
            //std::cout << x << ", " << y << std::endl;
            level1_platforms.push_back(level1_platform);
        }
        f_input.close();
        
//===============================================================================================================================    
    sf::Clock clock;
    float deltaTime = 0.0f;

    screen screenIndex = START;
    while(window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }


        window.clear();

        switch (screenIndex)
        {
        case START:

            if(playButton.isButtonPush(&window))
            {
                screenIndex = LEVEL1; 
            }
            else if(settingsButton.isButtonPush(&window))
            {
                screenIndex = SETTINGS;
            }

            settingsButton.Draw(&window);
            playButton.Draw(&window);

            break;

        case SETTINGS:
            //TODO: VOLUME SETTINGS
            break;

        case LEVEL1: //lvl 1

            for( Platform& p : level1_platforms)
            {
                player.colider.CheckColison(p, 0.0f);
                p.Draw(&window);
            }
            player.Update(deltaTime);
            player.Draw(&window);
            hp.Draw(&window);

            break;
        }

        window.display();
    }
}