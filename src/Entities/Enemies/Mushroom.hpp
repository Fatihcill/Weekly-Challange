#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include "AnimationManager.hpp"
#include "Enemy.hpp"

class Mushroom : public Enemy
{
private:
    AnimationManager::Animation crushed{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/mushroom/mushroom_crushed_anim_strip_6.png"), 6};
    AnimationManager::Animation death{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/mushroom/mushroom_death_anim_strip_6.png"), 6};
    AnimationManager::Animation hit{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/mushroom/mushroom_hit_anim_strip_3.png"), 3};
    AnimationManager::Animation walk{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/mushroom/mushroom_walk_anim_strip_8.png"), 8};
    AnimationManager::Animation idle{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/mushroom/mushroom_idle_anim_strip_3.png"), 3};

public:
    Mushroom(/* args */);
    ~Mushroom();
};

#endif