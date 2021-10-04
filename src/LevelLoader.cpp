
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Player.hpp"
#include "Colider.hpp"
#include "LevelLoader.hpp"
#include "Progressbar.hpp"
#include "ColidersMover.hpp"
#include "SaveManager.hpp"

LevelLoader::LevelLoader(Player* p_player, Progressbar* p_hp, bool* p_isKeyActivate, AdvanceColider* p_finish, SaveManager* p_saveManager)
: player(p_player), hp(p_hp), isKeyActivate(p_isKeyActivate), finish(p_finish), saveManager(p_saveManager), platforms(nullptr), bloodbags(nullptr), spikes(nullptr), saws(nullptr), keys(nullptr), lockedPlatforms(nullptr)
{}

void LevelLoader::LoadLevel(unsigned int lvl)
{
    bloodbags->clear();
    platforms->clear();
    spikes->clear();
    saws -> clear();
    colidersmovers -> clear();
    keys -> clear();
    lockedPlatforms -> clear();
    player->reset();
    *isKeyActivate = false; 

    std::ifstream f_input;
    std::stringstream FileName;
    float x, y;

    //PLAYER
    FileName.str("");
    FileName << "bin/levels/level" << 1 + lvl << "/player.txt";

    f_input.open(FileName.str().c_str());
    f_input >> x >> y;
    
    player -> SetPosition(x, y);
    
    f_input.close();

    //FINISH
    FileName.str("");
    FileName << "bin/levels/level" << 1 + lvl << "/finish.txt";

    f_input.open(FileName.str().c_str());
    f_input >> x >> y;
    
    finish -> setPosition(x, y);
    
    f_input.close();
    
    //HP
    if(lvl != 0)
    {
        hp->setProgress(saveManager -> getHpFromLevel(lvl - 1));
    }
    else
    {
        hp ->setProgress(1.0f);
    }
    



    //PLATFORMS
    if(platforms)
    {
        FileName.str("");
        FileName << "bin/levels/level" << 1 + lvl << "/terrain.txt";

        f_input.open(FileName.str().c_str());
        while (f_input >> x >> y)
        {
            platfromsSource[lvl].setPosition(x, y);
            platforms->push_back(platfromsSource[lvl]);
        }
        f_input.close();
    }
    
    //BLOOD BAGS
    if(bloodbags)
    {
        FileName.str("");
        FileName << "bin/levels/level" << 1 + lvl << "/bloodbags.txt";

        f_input.open(FileName.str().c_str());
        while (f_input >> x >> y)
        {
            bloodbagSource.setPosition(x, y);
            bloodbags->push_back(bloodbagSource);
        }
        f_input.close();
    }

    //SPIKES
    if(spikes)
    {
        FileName.str("");
        FileName << "bin/levels/level" << 1 + lvl << "/spikes.txt";

        f_input.open(FileName.str().c_str());
        while (f_input >> x >> y)
        {
            spikeSource.setPosition(x, y);
            spikes->push_back(spikeSource);
        }
        f_input.close();
    }

    //SAWS
    if(saws)
    {
        FileName.str("");
        FileName << "bin/levels/level" << 1 + lvl << "/saws.txt";

        f_input.open(FileName.str().c_str());
        while (f_input >> x >> y)
        {
            sawSource.setPosition(x, y);
            saws->push_back(sawSource);
        }
        f_input.close();
    }

    //KEYS
    if(keys)
    {
        FileName.str("");
        FileName << "bin/levels/level" << 1 + lvl << "/keys.txt";

        f_input.open(FileName.str().c_str());
        while (f_input >> x >> y)
        {
            keySource.setPosition(x, y);
            keys->push_back(keySource);
        }
        f_input.close();
    }

    //LOCKED PLATFORMS
    if(lockedPlatforms)
    {
        FileName.str("");
        FileName << "bin/levels/level" << 1 + lvl << "/lockedPlatforms.txt";

        f_input.open(FileName.str().c_str());
        while (f_input >> x >> y)
        {
            lockedPlatformSource.setPosition(x, y);
            lockedPlatforms->push_back(lockedPlatformSource);
        }
        f_input.close();
    }

    //COLIDER MOVERS
    if(colidersmovers)
    {
        FileName.str("");
        FileName << "bin/levels/level" << 1 + lvl << "/colidermovers.txt";

        float beginX, beginY, endX, endY, speed;

        f_input.open(FileName.str().c_str());
        while (f_input >> beginX >> beginY >> endX >> endY >> speed)
        {
            ColidersMover tmp(speed, sf::Vector2f(beginX, beginY), sf::Vector2f(endX, endY));

            std::string type;
            
            while(true)
            {
                f_input >> type;
                if(type == "end")
                {
                    break;
                }

                int index;
                f_input >> index;

                if(type == "P")
                {
                    tmp.add(&(*platforms)[index]);
                }
                else if(type == "Sp")
                {
                    tmp.add(&(*spikes)[index]);
                }
                else if(type == "Sa")
                {
                    tmp.add(&(*saws)[index]);
                }
                else if(type == "K")
                {
                    tmp.add(&(*keys)[index]);
                }
            }

            colidersmovers -> push_back(tmp);
            
        }
        f_input.close();

    }

}

void LevelLoader::setPlatforms( std::vector<AdvanceColider> p_platfromsSource, std::vector<AdvanceColider>* p_platforms)
{
    platfromsSource = p_platfromsSource;
    platforms = p_platforms;
}

void LevelLoader::setBloodbags(AdvanceColider p_bloodbagSource, std::vector<AdvanceColider>* p_bloodbags)
{
    bloodbagSource = p_bloodbagSource;
    bloodbags = p_bloodbags;
}

void LevelLoader::setSpikes(AdvanceColider p_spikeSource, std::vector<AdvanceColider>* p_spikes)
{
    spikeSource = p_spikeSource;
    spikes = p_spikes;
}

void LevelLoader::setColidersMovers(std::vector<ColidersMover>* p_colidersmovers)
{
    colidersmovers = p_colidersmovers;
}

void LevelLoader::setSaws(AdvanceColider p_sawSource, std::vector<AdvanceColider>* p_saws)
{
    sawSource = p_sawSource;
    saws = p_saws;
}

void LevelLoader::setKeys(AdvanceColider p_keySource, std::vector<AdvanceColider>* p_keys)
{
    keySource = p_keySource;
    keys = p_keys;
}

void LevelLoader::setLockedPlatforms(AdvanceColider p_lockedPlatformSource, std::vector<AdvanceColider>* p_lockedPlatforms)
{
    lockedPlatformSource = p_lockedPlatformSource;
    lockedPlatforms = p_lockedPlatforms;
}