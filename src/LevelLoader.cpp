
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Player.hpp"
#include "Platform.hpp"
#include "BloodBag.hpp"
#include "Colider.hpp"
#include "LevelLoader.hpp"
#include "Progressbar.hpp"

LevelLoader::LevelLoader(std::vector<Platform>* p_platforms, std::vector<BloodBag>* p_bloodbags, 
                         Player* p_player, Progressbar* p_hp, std::vector<Platform> p_platfromsSource, BloodBag p_bloodbagSource)
: platforms(p_platforms), bloodbags(p_bloodbags), player(p_player), hp(p_hp), platfromsSource(p_platfromsSource), bloodbagSource(p_bloodbagSource)
{}

void LevelLoader::LoadLevel(unsigned int lvl)
{
    bloodbags->clear();
    platforms->clear();

    switch (lvl)
    {
    case 0:
        player->SetPosition(200.0f, 200.0f);
        hp->setProgress(1.0f);
        break;
    }


    std::ifstream f_input;
    float x, y;

    std::stringstream terrainFileName;
    terrainFileName << "bin/levels/" << 1 + lvl << "terrain.txt";

    f_input.open(terrainFileName.str().c_str());
    while (f_input >> x >> y)
    {
        platfromsSource[lvl].setPosition(x, y);
        platforms->push_back(platfromsSource[lvl]);
    }
    f_input.close();
    

    std::stringstream bloodbagFileName;
    bloodbagFileName << "bin/levels/" << 1 + lvl << "bloodbags.txt";

    f_input.open(bloodbagFileName.str().c_str());
    while (f_input >> x >> y)
    {
        bloodbagSource.setPosition(x, y);
        bloodbags->push_back(bloodbagSource);
    }
    f_input.close();
}