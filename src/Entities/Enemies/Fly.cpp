#include "Fly.hpp"

Fly::Fly(int type) 
{
    if (type == ORANGE_FLY)
    {
        attack = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/orange_fly_attack_anim_strip_3"), 3};
        hit = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/orange_fly_hit_anim_strip_3.png"), 3};
        death = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/orange_fly_death_anim_strip_5.png"), 5};
        flying = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/orange_fly_idle_or_flying_anim_strip_3.png"), 3};
    }
    else if (type == BLUE_FLY)
    {
        attack = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/blue_fly_attack_anim_strip_3"), 3};
        hit = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/blue_fly_hit_anim_strip_3.png"), 3};
        death = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/blue_fly_death_anim_strip_5.png"), 5};
        flying = AnimationManager::Animation{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/enemies sprites/fly/blue_fly_idle_or_flying_anim_strip_3.png"), 3};
    }
}

Fly::~Fly() 
{
    UnloadTexture(death.anim_texture);
    UnloadTexture(hit.anim_texture);
    UnloadTexture(attack.anim_texture);
    UnloadTexture(flying.anim_texture);
}

void Fly::enemyInit() 
{
    
}

void Fly::enemyUpdate(const float &dt) 
{
    
}

void Fly::enemyDraw() 
{
    
}

