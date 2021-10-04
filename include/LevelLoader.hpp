#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.hpp"
#include "AdvanceColider.hpp"
#include "Colider.hpp"
#include "Progressbar.hpp"
#include "ColidersMover.hpp"

class LevelLoader
{
public:
    LevelLoader(Player* p_player, Progressbar* p_hp, bool* p_isKeyActivate);

    void LoadLevel(unsigned int lvl);
    void setPlatforms( std::vector<AdvanceColider> p_platfromsSource, std::vector<AdvanceColider>* p_platforms);
    void setBloodbags(AdvanceColider p_bloodbagSource, std::vector<AdvanceColider>* p_bloodbags);
    void setSpikes(AdvanceColider p_spikeSource, std::vector<AdvanceColider>* p_spikes);
    void setSaws(AdvanceColider p_sawSource, std::vector<AdvanceColider>* p_saws);
    void setKeys(AdvanceColider p_keySource, std::vector<AdvanceColider>* p_keys);
    void setLockedPlatforms(AdvanceColider p_lockedPlatformSource, std::vector<AdvanceColider>* p_lockedPlatforms);
    void setColidersMovers(std::vector<ColidersMover>* p_colidersmovers);
    
private:
    Player* player;
    Progressbar* hp;
    bool* isKeyActivate;

    std::vector<AdvanceColider> platfromsSource;
    std::vector<AdvanceColider>* platforms;

    AdvanceColider bloodbagSource;
    std::vector<AdvanceColider>* bloodbags;

    AdvanceColider spikeSource;
    std::vector<AdvanceColider>* spikes;

    AdvanceColider sawSource;
    std::vector<AdvanceColider>* saws;

    AdvanceColider keySource;
    std::vector<AdvanceColider>* keys;

    AdvanceColider lockedPlatformSource;
    std::vector<AdvanceColider>* lockedPlatforms;

    std::vector<ColidersMover>* colidersmovers;

    
};