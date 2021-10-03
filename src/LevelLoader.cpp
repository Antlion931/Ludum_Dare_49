
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Player.hpp"
#include "Colider.hpp"
#include "LevelLoader.hpp"
#include "Progressbar.hpp"
#include "ColidersMover.hpp"

LevelLoader::LevelLoader(Player* p_player, Progressbar* p_hp)
: player(p_player), hp(p_hp), platforms(nullptr), bloodbags(nullptr), spikes(nullptr), saws(nullptr)
{}

void LevelLoader::LoadLevel(unsigned int lvl)
{
    bloodbags->clear();
    platforms->clear();
    spikes->clear();
    saws -> clear();
    colidersmovers -> clear();
    player->reset();

    switch (lvl)
    {
    case 0:
        player->SetPosition(200.0f, 200.0f);
        hp->setProgress(1.0f);
        break;
    }


    std::ifstream f_input;
    std::stringstream FileName;
    float x, y;

    //PLATFORMS
    if(platforms)
    {
        FileName.str("");
        FileName << "bin/levels/" << 1 + lvl << "terrain.txt";

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
        FileName << "bin/levels/" << 1 + lvl << "bloodbags.txt";

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
        FileName << "bin/levels/" << 1 + lvl << "spikes.txt";

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
        FileName << "bin/levels/" << 1 + lvl << "saws.txt";

        f_input.open(FileName.str().c_str());
        while (f_input >> x >> y)
        {
            sawSource.setPosition(x, y);
            saws->push_back(sawSource);
        }
        f_input.close();
    }

    //COLIDER MOVERS
    if(colidersmovers)
    {
        FileName.str("");
        FileName << "bin/levels/" << 1 + lvl << "colidermovers.txt";

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
                else if(type == "B")
                {
                    tmp.add(&(*bloodbags)[index]);
                }
                else if(type == "Sp")
                {
                    tmp.add(&(*spikes)[index]);
                }
                else if(type == "Sa")
                {
                    tmp.add(&(*saws)[index]);
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
