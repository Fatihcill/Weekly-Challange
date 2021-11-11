#ifndef WORM_HPP
#define WORM_HPP

#include "AnimationManager.hpp"
#include "Enemy.hpp"

class Worm : public Enemy
{
private:
    AnimationManager::Animation death{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/worm/worm_death_anim_strip_6.png"), 6};
    AnimationManager::Animation hit{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/worm/worm_hit_anim_strip_3.png"), 3};
    AnimationManager::Animation walk{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/worm/worm_walk_anim_strip_6.png"), 6};
    void enemyInit();
    void enemyUpdate(const float &dt);
    void enemyDraw();
public:
    Worm(/* args */);
    ~Worm();
};

#endif