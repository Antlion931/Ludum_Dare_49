#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.hpp"
#include "Platform.hpp"
#include "BloodBag.hpp"
#include "Colider.hpp"
#include "Progressbar.hpp"

class LevelLoader
{
public:
    LevelLoader(std::vector<Platform>* p_platforms, std::vector<BloodBag>* p_bloodbags, Player* p_player, Progressbar* p_hp,  std::vector<Platform> p_platfromsSource, BloodBag p_bloodbagSource);

    void LoadLevel(unsigned int lvl);
private:
    std::vector<Platform>* platforms;
    std::vector<BloodBag>* bloodbags;
    std::vector<Platform> platfromsSource;
    BloodBag bloodbagSource;

    Player* player;

    Progressbar* hp;
    

};