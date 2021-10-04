#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "SaveManager.hpp"

float SaveManager::getHpFromLevel(unsigned int level)
{
    std::ifstream f_input;
    f_input.open("bin/save/save.txt");
    float hp;
    unsigned int lvl;

    while(f_input >> lvl >> hp)
    {
        if(lvl == level)
        {
            return hp;
        }
    }

    f_input.close();
    return 0.0f;
}

void SaveManager::addHpToLevel(unsigned int level, float p_hp)
{
    //std::cout << level << " " << p_hp << std::endl;
    std::ifstream f_input;
    float hps[7] = {};
    float hp;
    unsigned int lvl;
    f_input.open("bin/save/save.txt");

    while(f_input >> lvl >> hp)
    {
        hps[lvl] = hp;
    }

    f_input.close();

    hps[level] += p_hp;

    // for(int i = level; i < 7; i++)
    // {
    //     if(hps[i] >= 1.0f)
    //     {
    //         break;
    //     }
    //     else if(hps[i] == 0.0f)
    //     {
    //         hps[i] += p_hp;
    //         break;
    //     }

    //     hps[i] += p_hp;

    //     if(hps[i] >= 1.0f)
    //     {
    //         p_hp = hps[i] - 1.0f;
    //         hps[i] = 1.0f;
    //     }

    //     //std::cout << "i: " << i << ", p_hp: " << p_hp << ", hp:" << hp << ", hps[i]:" << hps[i] << std::endl; 
    // }

    std::ofstream f_output;
    f_output.open("bin/save/save.txt");

    for(int i = 0; i < 7; i++)
    {
        if(hps[i] != 0.0f)
        {
            f_output << i << " " << hps[i] << std::endl;
        }
        else
        {
            break;
        }
    }

    f_output.close();
}

long int SaveManager::getScore()
{
    long int score = 0;
    for(int i = 0; i < 7; i++)
    {
        score += getHpFromLevel(i) * 10000;
    }

    return score;
}

