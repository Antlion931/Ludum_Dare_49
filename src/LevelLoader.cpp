
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Player.hpp"
#include "Colider.hpp"
#include "LevelLoader.hpp"
#include "Progressbar.hpp"

LevelLoader::LevelLoader(Player* p_player, Progressbar* p_hp)
: player(p_player), hp(p_hp), platforms(nullptr), bloodbags(nullptr), spikes(nullptr)
{}

void LevelLoader::LoadLevel(unsigned int lvl)
{
    bloodbags->clear();
    platforms->clear();
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
    FileName.str("");
    FileName << "bin/levels/" << 1 + lvl << "terrain.txt";

    f_input.open(FileName.str().c_str());
    while (f_input >> x >> y)
    {
        platfromsSource[lvl].setPosition(x, y);
        platforms->push_back(platfromsSource[lvl]);
    }
    f_input.close();
    
    //BLOOD BAGS
    FileName.str("");
    std::cout << FileName.str() << std::endl;
    FileName << "bin/levels/" << 1 + lvl << "bloodbags.txt";

    f_input.open(FileName.str().c_str());
    while (f_input >> x >> y)
    {
        bloodbagSource.setPosition(x, y);
        bloodbags->push_back(bloodbagSource);
    }
    f_input.close();

    //SPIKES
    FileName.str("");
    std::cout << FileName.str() << std::endl;
    FileName << "bin/levels/" << 1 + lvl << "spikes.txt";

    f_input.open(FileName.str().c_str());
    while (f_input >> x >> y)
    {
        spikeSource.setPosition(x, y);
        spikes->push_back(spikeSource);
    }
    f_input.close();

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
