#include <iostream>
#include <fstream>
#include <sstream>
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
#include "SaveManager.hpp"

enum screen
{
    START,
    SETTINGS,
    LEVELS,
    GAME
};

enum lvl
{
    LEVEL1 = 0,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6,
    LEVEL7
};

int main()
{
    float masterVolume = 1.0f;

    //WINDOW
    sf::RenderWindow window(sf::VideoMode(1300, 720), "The Game", sf::Style::Close | sf::Style::Titlebar);

    //MUSIC
    sf::Music mainTheme;
    mainTheme.openFromFile("res/Heart monitor remix.wav");
    mainTheme.setLoop(true);
    mainTheme.play();

    sf::Music bloodBagPickUpMusic;
    bloodBagPickUpMusic.openFromFile("res/blood-bagPickUp.wav");

    sf::Music hurtMusic;
    hurtMusic.openFromFile("res/hurt.wav");

    sf::Music keyPickUpMusic;
    keyPickUpMusic.openFromFile("res/keyPickUp.wav");

    //FONT
    sf::Font font;
    font.loadFromFile("res/pixel-combat-font/PixelCombat-Wajz.ttf");

    //SAVER MANAGER
    SaveManager saveManager;

    //PLAYER
    sf::Texture playerIdleTexture, playerRunTexture, playerJumpTexture;

    playerIdleTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Idle (32x32).png");
    playerRunTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Run (32x32).png");
    playerJumpTexture.loadFromFile("res/Free/Main Characters/Virtual Guy/Jump (32x32).png");

    Player player(200.0f, 175.0f, 1.0f, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(33.0f, 47.0f));

    player.setIdle(&playerIdleTexture, 11, 0.1f);
    player.setRun(&playerRunTexture, 12, 0.05f);
    player.setJump(&playerJumpTexture, 1, 10.0f);

    //FINISH
    sf::Texture finishtexture;
    finishtexture.loadFromFile("res/Free/Items/Checkpoints/End/End (Idle).png");
    AdvanceColider finish(finishtexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(60.0f, 60.0f));

    //FILE STREAM
    std::ifstream f_input;
    float x, y;

    //PROGRESBAR
    Progressbar hp(1300.0f, 70.0f, sf::Color(100, 100, 100), sf::Color::Red);
    hp.setPosition(0.0f, 0.0f);
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

        sf::Text resetButtonText;
        resetButtonText.setFont(font);
        resetButtonText.setCharacterSize(50);
        resetButtonText.setPosition(310.0f, 120.0f);
        resetButtonText.setString("RESET ALL PROGRESS");

        Button resetButton(&resetButtonText, sf::Color::Black, sf::Color::White, sf::Vector2f(700.0f, 100.0f));
        resetButton.setPosition(300.0f, 100.0f);

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


    //LEVELS
        sf::Text levelsText;
        levelsText.setFont(font);
        levelsText.setCharacterSize(27);
        levelsText.setString("You are playing as unstable patient after car accident,\n" 
                             "your task is to don't bleed out and complite all levels,\n" 
                             "sometimes you will have to go back to previous levels,\n"
                             "to save more blood for next levels.\n"
                             "A - go left\n"
                             "D - go right\n"
                             "W - jump\n"
                             "R - quick reset\n");
        levelsText.setPosition(180.0f, 10.0f);

        sf::Text score;
        score.setFont(font);
        score.setCharacterSize(30);
        score.setPosition(50.0f, 470.0f);

        sf::Text win;
        win.setFont(font);
        win.setCharacterSize(30);
        win.setPosition(700.0f, 470.0f);
        win.setString("YOU WIN!");



        sf::Texture level1Texture;
        level1Texture.loadFromFile("res/Free/Menu/Levels/01.png");
        Button level1Button(&level1Texture, sf::Vector2f(100.0f, 100.0f));
        level1Button.setPosition(50.0f, 500.0f);

        Progressbar level1Hp(100.0f, 10.0f, sf::Color(100, 100, 100), sf::Color::Red);
        level1Hp.setPosition(50.0f, 610.0f);

        sf::Texture level2Texture;
        level2Texture.loadFromFile("res/Free/Menu/Levels/02.png");
        Button level2Button(&level2Texture, sf::Vector2f(100.0f, 100.0f));
        level2Button.setPosition(250.0f, 500.0f);

        Progressbar level2Hp(100.0f, 10.0f, sf::Color(100, 100, 100), sf::Color::Red);
        level2Hp.setPosition(250.0f, 610.0f);

        sf::Texture level3Texture;
        level3Texture.loadFromFile("res/Free/Menu/Levels/03.png");
        Button level3Button(&level3Texture, sf::Vector2f(100.0f, 100.0f));
        level3Button.setPosition(450.0f, 500.0f);

        Progressbar level3Hp(100.0f, 10.0f, sf::Color(100, 100, 100), sf::Color::Red);
        level3Hp.setPosition(450.0f, 610.0f);

        sf::Texture level4Texture;
        level4Texture.loadFromFile("res/Free/Menu/Levels/04.png");
        Button level4Button(&level4Texture, sf::Vector2f(100.0f, 100.0f));
        level4Button.setPosition(650.0f, 500.0f);

        Progressbar level4Hp(100.0f, 10.0f, sf::Color(100, 100, 100), sf::Color::Red);
        level4Hp.setPosition(650.0f, 610.0f);

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

        platformTextureRect.height = 48;
        platformTextureRect.width = 48;
        platformTextureRect.left = 96;
        platformTextureRect.top = 0;
        AdvanceColider lvl1(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(lvl1);

        platformTextureRect.height = 48;
        platformTextureRect.width = 48;
        platformTextureRect.left = 96;
        platformTextureRect.top = 48 + 16;
        AdvanceColider lvl2(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(lvl2);

        platformTextureRect.height = 48;
        platformTextureRect.width = 48;
        platformTextureRect.left = 96;
        platformTextureRect.top = 96 + 32;
        AdvanceColider lvl3(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(lvl3);

        platformTextureRect.height = 48;
        platformTextureRect.width = 48;
        platformTextureRect.left = 0;
        platformTextureRect.top = 0;
        AdvanceColider lvl4(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(lvl4);

        platformTextureRect.height = 48;
        platformTextureRect.width = 48;
        platformTextureRect.left = 0;
        platformTextureRect.top = 48 + 16;
        AdvanceColider lvl5(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(lvl5);

        platformTextureRect.height = 48;
        platformTextureRect.width = 48;
        platformTextureRect.left = 0;
        platformTextureRect.top = 96 + 32;
        AdvanceColider lvl6(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(lvl6);

        platformTextureRect.height = 48;
        platformTextureRect.width = 48;
        platformTextureRect.left = 96 * 2 + 48 + 32;
        platformTextureRect.top = 48 + 16;
        AdvanceColider lvl7(terrain, sf::Vector2f(50.0f, 50.0f), &platformTextureRect);
        platformsSource.push_back(lvl7);

        //SPIKES
        sf::Texture spikeTexture;
        spikeTexture.loadFromFile("res/Free/Traps/Spikes/Idle.png");
        AdvanceColider spikeSource(spikeTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(48.0f, 20.0f), 0.0f, 15.0f);

        //KEYS
        sf::Texture keyTexture;
        keyTexture.loadFromFile("res/key.png");
        AdvanceColider keySource(keyTexture, sf::Vector2f(32.0f, 32.0f));

        //LOCKED PLATFORMS
        sf::Texture lockedPlatformTexture;
        lockedPlatformTexture.loadFromFile("res/Free/Traps/Blocks/Idle.png");

        sf::IntRect lockedPlatformTextureRect;
        lockedPlatformTextureRect.height = 16;
        lockedPlatformTextureRect.width = 16;
        lockedPlatformTextureRect.left = 3;
        lockedPlatformTextureRect.top = 3;
        AdvanceColider lockedPlatformSource(lockedPlatformTexture, sf::Vector2f(50.0f, 50.0f), &lockedPlatformTextureRect);

        //SAWS
        sf::Texture sawTexture;
        sawTexture.loadFromFile("res/Free/Traps/Saw/On (38x38).png");
        AdvanceColider sawSource(sawTexture, 8, 0.01f, sf::Vector2f(30.0f, 30.0f));


        std::vector<AdvanceColider> platforms;
        std::vector<AdvanceColider> bloodbags;
        std::vector<AdvanceColider> spikes;
        std::vector<AdvanceColider> saws;
        std::vector<AdvanceColider> keys;
        std::vector<AdvanceColider> lockedPlatforms;
        std::vector<ColidersMover> colidersmovers;

        bool isKeyActivate = false;

        LevelLoader levelloader(&player, &hp, &isKeyActivate, &finish, &saveManager);

        levelloader.setPlatforms(platformsSource, &platforms);
        levelloader.setBloodbags(bloodbagSource, &bloodbags);
        levelloader.setSpikes(spikeSource, &spikes);
        levelloader.setSaws(sawSource, &saws);
        levelloader.setKeys(keySource, &keys);
        levelloader.setLockedPlatforms(lockedPlatformSource, &lockedPlatforms);
        levelloader.setColidersMovers(&colidersmovers);

        
//===============================================================================================================================    
    sf::Clock clock;
    float deltaTime = 0.0f;

    std::stringstream newScore;
    screen screenIndex = START;
    unsigned int level = LEVEL1;

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
                //levelloader.LoadLevel(level);
                screenIndex = LEVELS; 
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
            resetButton.Draw(&window);

            if(resetButton.isButtonPush(&window))
            {
                std::ofstream file;
                file.open("bin/save/save.txt");
                file.close();
            }

            if(backFromSettings.isButtonPush(&window))
            {
                screenIndex = START;
            }
            volumebar.Update(&window, &masterVolume);


            break;

        case LEVELS:

            level1Button.Draw(&window);
            level1Hp.setProgress(saveManager.getHpFromLevel(0));
            level1Hp.Draw(&window);
            backFromSettings.Draw(&window);
            window.draw(levelsText);

            newScore.str("");
            newScore << "Score: " << saveManager.getScore();
            score.setString(newScore.str());
            window.draw(score);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                levelloader.LoadLevel(level);
                screenIndex = GAME;
            }

            if(backFromSettings.isButtonPush(&window))
            {
                screenIndex = START;
            }

            if(level1Button.isButtonPush(&window))
            {
                level = 0;
                levelloader.LoadLevel(level);
                screenIndex = GAME;
            }

            if(saveManager.getHpFromLevel(0) > 0.0f)
            {
                level2Button.Draw(&window);
                level2Hp.setProgress(saveManager.getHpFromLevel(1));
                level2Hp.Draw(&window);

                if(level2Button.isButtonPush(&window))
                {
                    level = 1;
                    levelloader.LoadLevel(level);
                    screenIndex = GAME;
                }
            }

            if(saveManager.getHpFromLevel(1) > 0.0f)
            {
                level3Button.Draw(&window);
                level3Hp.setProgress(saveManager.getHpFromLevel(2));
                level3Hp.Draw(&window);

                if(level3Button.isButtonPush(&window))
                {
                    level = 2;
                    levelloader.LoadLevel(level);
                    screenIndex = GAME;
                }
            }

            if(saveManager.getHpFromLevel(2) > 0.0f)
            {
                level4Button.Draw(&window);
                level4Hp.setProgress(saveManager.getHpFromLevel(3));
                level4Hp.Draw(&window);
                window.draw(win);

                if(level4Button.isButtonPush(&window))
                {
                    level = 3;
                    levelloader.LoadLevel(level);
                    screenIndex = GAME;
                }
            }


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

                p.Draw(&window, deltaTime);
            }

            int bloodbag_index = 0;
            for(AdvanceColider& b : bloodbags)
            {
                b.Draw(&window, deltaTime);

                if(player.colider.CheckColison(b, 0.0f))
                {
                    hp.changeProgress(0.3f);
                    b.setPosition(-1000.0f, -1000.0f);
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
                s.Draw(&window, deltaTime);

                if(!player.isInvincible() && player.colider.CheckColison(s, 0.0f))
                {
                    hurtMusic.setVolume(masterVolume * 100);
                    hurtMusic.stop();
                    hurtMusic.play();
                    hp.changeProgress(-0.1f);
                    player.setInvincible();
                }
            }

            for(AdvanceColider& s : saws)
            {
                s.Draw(&window, deltaTime);

                if(!player.isInvincible() && player.colider.CheckColison(s, 0.0f))
                {
                    hurtMusic.setVolume(masterVolume * 100);
                    hurtMusic.stop();
                    hurtMusic.play();
                    hp.changeProgress(-0.4f);
                    player.setInvincible();
                }
            }

            if(!isKeyActivate)
            {
                for(AdvanceColider& k : keys)
                {
                    k.Draw(&window, deltaTime);

                    if(player.colider.CheckColison(k, false))
                    {
                        keyPickUpMusic.setVolume(masterVolume * 100);
                        keyPickUpMusic.stop();
                        keyPickUpMusic.play();
                        isKeyActivate = true;
                    }
                }

                for(AdvanceColider& l : lockedPlatforms)
                {
                    player.colider.CheckColison(l, 0.0f);
                    if(player.groundColider.CheckColison(l, 0.0f, false))
                    {
                        player.setIsOnGround(true);
                    }

                    if(player.ceilingColider.CheckColison(l, 0.0f, false))
                    {
                        player.hitCeiling();
                    }
                    l.Draw(&window, deltaTime);
                }


            }

            if(hp.getProgress() == 0.0f)
            {
                screenIndex = LEVELS;
            }
            
            if(player.colider.CheckColison(finish, 0.0f, false))
            {
                saveManager.addHpToLevel(level, hp.getProgress());
                screenIndex = LEVELS;
                break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                levelloader.LoadLevel(level);
                break;
            }
            player.Update(deltaTime);
            player.Draw(&window, deltaTime);
            finish.Draw(&window, deltaTime);
            hp.Draw(&window);

            break;
        }

        window.display();
    }
}