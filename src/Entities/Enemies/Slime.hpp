#ifndef SLIME_HPP
#define SLIME_HPP

#include "AnimationManager.hpp"
#include "Enemy.hpp"

class Slime : public Enemy
{
private:
    AnimationManager::Animation death{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/slime/slime_death_anim_strip_6.png"), 6};
    AnimationManager::Animation hit{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/slime/slime_hit_anim_strip_3.png"), 3};
    AnimationManager::Animation walk{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/slime/slime_walk_anim_strip_15.png"), 15};
    AnimationManager::Animation idle{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/slime/slime_idle_anim_strip_5.png"), 5};

public:
    Slime(/* args */);
    ~Slime();
};

#endif