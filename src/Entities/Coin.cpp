#include "Coin.hpp"
#include <iostream>
Coin::Coin(float x, float y)
{
    hasTaken = false;
    pos.x = x;
    pos.y = y;
    source = Rectangle{animmanager.getFrame() * animmanager.animwidth, 0.f, animmanager.animwidth, animmanager.getAnim().anim_texture.height};
    dest  = Rectangle{pos.x, pos.y, animmanager.animwidth, animmanager.getAnim().anim_texture.height};
}

Coin::~Coin() 
{
    UnloadTexture(coin.anim_texture);
    UnloadTexture(coinpickup.anim_texture);
}

void Coin::update(Entity &player)
{
   
    if (!hasTaken)
    {
        animmanager.setAnim(coin);

        if (CheckCollisionRecs(dest, player.entityrec))
        {
            animmanager.setAnim(coinpickup);
            hasTaken = true;
        }
        dest.width = animmanager.animwidth;
        dest.height = animmanager.getAnim().anim_texture.height;
    }
    
    animmanager.playAnim();
}

void Coin::draw() 
{
#ifndef NDEBUG
    DrawRectangleLinesEx(dest, 1.f, YELLOW);
#endif
    source.x = animmanager.getFrame() * animmanager.animwidth;
    source.width = animmanager.animwidth;
    DrawTexturePro(animmanager.getAnim().anim_texture, source, dest, Vector2{}, 0.f, WHITE);
}

