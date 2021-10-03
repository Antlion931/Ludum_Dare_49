#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Button.hpp"
#include "Player.hpp"
#include "Colider.hpp"
#include "Animation.hpp"
#include "Progressbar.hpp"
#include "VolumeBar.hpp"
#include "LevelLoader.hpp"
#include "AdvanceColider.hpp"
#include "ColidersMover.hpp"

enum screen
{
    START = 100,
    SETTINGS = 101,
    GAME = 102,
    LEVEL0 = 0
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

    sf::Music bloodBagPickUpMusic;
    bloodBagPickUpMusic.openFromFile("res/blood-bagPickUp.wav");

    sf::Music hurtMusic;
    hurtMusic.openFromFile("res/hurt.wav");

    //FONT
    sf::Font font;
    font.loadFromFile("res/pixel-combat-font/PixelCombat-Wajz.ttf");

    //PLAYER
    sf::Texture playerIdleTexture, playerRunTexture, playerJumpTexture;

    playerIdleTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Idle (32x32).png");
    playerRunTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Run (32x32).png");
    playerJumpTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Jump (32x32).png");

    Player player(200.0f, 150.0f, 1.0f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(66.0f, 94.0f));

    player.setIdle(&playerIdleTexture, 11, 0.1f);
    player.setRun(&playerRunTexture, 12, 0.05f);
    player.setJump(&playerJumpTexture, 1, 10.0f);

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


    //LEVEL LOADER SET UP

        //BLOOD BAGS
        sf::Texture bloodBagTexture;
        bloodBagTexture.loadFromFile("res/blood-bag.png");
        AdvanceColider bloodbagSource(bloodBagTexture, sf::Vector2f(32.0f, 32.0f));

        //PLATFORMS
        sf::Texture terrain;
        terrain.loadFromFile("res/Free/Terrain/Terrain (16x16).png");

        sf::IntRect platformTextureRect;
        std::vector<AdvanceColider> platformsSource;

        platformTextureRect.height = 16;
        platformTextureRect.width = 16;
        platformTextureRect.left = 0;
        platformTextureRect.top = 0;
        AdvanceColider platform(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(platform);

        //SPIKES
        sf::Texture spikeTexture;
        spikeTexture.loadFromFile("res/Free/Traps/Spikes/Idle.png");
        AdvanceColider spikeSource(spikeTexture, sf::Vector2f(50.0f, 50.0f));

        std::vector<AdvanceColider> platforms;
        std::vector<AdvanceColider> bloodbags;
        std::vector<AdvanceColider> spikes;
        std::vector<ColidersMover> colidersmovers;

        LevelLoader levelloader(&player, &hp);

        levelloader.setPlatforms(platformsSource, &platforms);
        levelloader.setBloodbags(bloodbagSource, &bloodbags);
        levelloader.setSpikes(spikeSource, &spikes);
        levelloader.setColidersMovers(&colidersmovers);

        
//===============================================================================================================================    
    sf::Clock clock;
    float deltaTime = 0.0f;

    screen screenIndex = START;
    while(window.isOpen())
    {
        mainTheme.setVolume(masterVolume * 25);
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
                levelloader.LoadLevel(LEVEL0);
                screenIndex = GAME; 
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

        case GAME: //lvl 1

            hp.changeProgress(-0.1f * deltaTime);
            player.setIsOnGround(false);
            
            for(ColidersMover& c : colidersmovers)
            {
                c.Update(deltaTime);
            }
            
            for( AdvanceColider& p : platforms)
            {

                player.colider.CheckColison(p, 0.0f);

                if(player.groundColider.CheckColison(p, 0.0f, false))
                {
                    player.setIsOnGround(true);
                }

                if(player.ceilingColider.CheckColison(p, 0.0f, false))
                {
                    player.hitCeiling();
                }

                p.Draw(&window);
            }

            int bloodbag_index = 0;
            for(AdvanceColider& b : bloodbags)
            {
                b.Draw(&window);

                if(player.colider.CheckColison(b, false))
                {
                    hp.changeProgress(0.3f);
                    bloodbags.erase(bloodbags.begin() + bloodbag_index);
                    bloodBagPickUpMusic.setVolume(masterVolume * 100);
                    bloodBagPickUpMusic.stop();
                    bloodBagPickUpMusic.play();
                }
                else
                {
                    ++bloodbag_index;
                }
            }

            for(AdvanceColider& s : spikes)
            {
                s.Draw(&window);

                if(!player.isInvincible() && player.colider.CheckColison(s, false))
                {
                    hurtMusic.setVolume(masterVolume * 100);
                    hurtMusic.stop();
                    hurtMusic.play();
                    hp.changeProgress(-0.2f);
                    player.setInvincible();
                }
            }

            

            if(hp.getProgress() == 0.0f)
            {
                screenIndex = START;
            }

            player.Update(deltaTime);
            player.Draw(&window, deltaTime);
            hp.Draw(&window);

            break;
        }

        window.display();
    }
}