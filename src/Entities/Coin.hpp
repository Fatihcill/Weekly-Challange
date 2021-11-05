#ifndef COIN_HPP
#define COIN_HPP

#include "AnimationManager.hpp"
#include "Entity.hpp"

class Coin
{
private:
    Vector2 pos{0, 0};
    AnimationManager::Animation coin{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/miscellaneous sprites/coin_anim_strip_6.png"), 6};
    AnimationManager::Animation coinpickup{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/miscellaneous sprites/coin_pickup_anim_strip_7.png"), 7};
    Rectangle source;
    Rectangle dest;
public:
    Coin(float x, float y);
    ~Coin();
    void draw();
    void update(Entity &player);
    bool hasTaken = false;
    AnimationManager animmanager{coin};
};

#endif