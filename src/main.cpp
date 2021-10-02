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
#include "BloodBag.hpp"
#include "VolumeBar.hpp"

enum screen
{
    START,
    SETTINGS,
    LEVEL1
};

int main()
{
    float masterVolume = 1.0f;

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

    //BLOOD BAG TEXTURE
    sf::Texture bloodBagTexture;
    bloodBagTexture.loadFromFile("res/blood-bag.png");
    sf::Music bloodBagPickUpMusic;
    bloodBagPickUpMusic.openFromFile("res/blood-bagPickUp.wav");

    //PLAYER
    sf::Texture playerIdleTexture, playerRunTexture, playerJumpTexture;

    playerIdleTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Idle (32x32).png");
    playerRunTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Run (32x32).png");
    playerJumpTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Jump (32x32).png");

    Player player(&playerIdleTexture, 11, 0.1f, &playerRunTexture, 12, 0.05f, &playerJumpTexture, 1, 10.0f, 200.0f, 150.0f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(66.0f, 94.0f));

    //FILE STREAM
    std::ifstream f_input;
    float x, y;

    //PROGRESBAR
    Progressbar hp(1260.0f, 30.0f, sf::Color(100, 100, 100), sf::Color::Red);
    hp.setPosition(10.0f, 10.0f);
    hp.setProgress(1.0f);

//======================================================================================================================
    //START
        //PLAY BUTTON
        sf::Text playButtonText;
        playButtonText.setFont(font);
        playButtonText.setCharacterSize(150);
        playButtonText.setPosition(410.0f, 100.0f);
        playButtonText.setString("PLAY");

        Button playButton(&playButtonText, sf::Color::Black, sf::Color::White, sf::Vector2f(500.0f, 200.0f));
        playButton.setPosition(390.0f, 100.0f);

        //SETTINGS BUTTON
        sf::Texture settingsButtonTexture;
        settingsButtonTexture.loadFromFile("res/Free/Menu/Buttons/Settings.png");
        
        Button settingsButton(&settingsButtonTexture, sf::Vector2f(100.0f, 100.0f));
        settingsButton.setPosition(50.0f, 570.0f);

    //SETTINGS
        sf::Texture backFromSettingsTexture;
        backFromSettingsTexture.loadFromFile("res/Free/Menu/Buttons/Back.png");
        Button backFromSettings(&backFromSettingsTexture, sf::Vector2f(100.0f, 100.0f));
        backFromSettings.setPosition(10.0f, 10.0f);

        sf::Texture volumeTexture;
        volumeTexture.loadFromFile("res/Free/Menu/Buttons/Volume.png");
        Button volumeTestButton(&volumeTexture, sf::Vector2f(100.0f, 100.0f));
        volumeTestButton.setPosition(300.0f, 300.0f);

        VolumeBar volumebar(660.0f, 100.0f, sf::Color(100.0f, 100.0f, 100.0f), sf::Color::White);
        volumebar.setProgress(masterVolume);
        volumebar.setPosition(410.0f, 300.0f);


    //1 LEVEL
        sf::IntRect level1_textureRect;
        level1_textureRect.height = 16;
        level1_textureRect.width = 16;
        level1_textureRect.left = 0;
        level1_textureRect.top = 0;

        Platform level1_platform(terrain,level1_textureRect, sf::Vector2f(50.0f, 50.0f));
        std::vector<Platform> level1_platforms;

        f_input.open("bin/levels/1terrein.txt");
        while (f_input >> x >> y)
        {
            level1_platform.setPosition(x, y);
            //std::cout << x << ", " << y << std::endl;
            level1_platforms.push_back(level1_platform);
        }
        f_input.close();

        BloodBag level1_bloodbag(&bloodBagTexture, sf::Vector2f(32.0f, 32.0f));
        std::vector<BloodBag> level1_bloodbags;

        f_input.open("bin/levels/1bloodbags.txt");
        while (f_input >> x >> y)
        {
            level1_bloodbag.setPosition(x, y);
            level1_bloodbags.push_back(level1_bloodbag);
        }
        f_input.close();
        
        
//===============================================================================================================================    
    sf::Clock clock;
    float deltaTime = 0.0f;

    screen screenIndex = START;
    while(window.isOpen())
    {
        mainTheme.setVolume(masterVolume * 100);
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
            volumebar.Draw(&window);
            volumeTestButton.Draw(&window);
            backFromSettings.Draw(&window);

            if(backFromSettings.isButtonPush(&window))
            {
                screenIndex = START;
            }
            volumebar.Update(&window, &masterVolume);


            break;

        case LEVEL1: //lvl 1

            hp.changeProgress(-0.1f * deltaTime);
            player.setIsOnGround(false);
            for( Platform& p : level1_platforms)
            {

                player.colider.CheckColison(p, 0.0f);

                if(player.groundColider.CheckColison(p, 0.0f, false))
                {
                    player.setIsOnGround(true);
                }

                p.Draw(&window);
            }

            int bloodbag_index = 0;
            for(BloodBag& b : level1_bloodbags)
            {
                b.Draw(&window);

                if(player.colider.CheckColison(b, false))
                {
                    hp.changeProgress(0.3f);
                    level1_bloodbags.erase(level1_bloodbags.begin() + bloodbag_index);
                    bloodBagPickUpMusic.setVolume(masterVolume * 100);
                    bloodBagPickUpMusic.play();
                }
                else
                {
                    ++bloodbag_index;
                }
            }
            player.Update(deltaTime);
            player.Draw(&window, deltaTime);
            hp.Draw(&window);

            break;
        }

        window.display();
    }
}