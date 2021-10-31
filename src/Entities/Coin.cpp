#include "Coin.hpp"
#include <iostream>
Coin::Coin(float x, float y)
{
    hasTaken = false;
    scale = 2;
    pos.x = x;
    pos.y = y;
    source = Rectangle{animmanager.getFrame() * animmanager.animwidth, 0.f, animmanager.animwidth, animmanager.getAnim().anim_texture.height};
    dest  = Rectangle{pos.x, pos.y, animmanager.animwidth * scale, animmanager.getAnim().anim_texture.height * scale};
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
        dest.width = animmanager.animwidth * scale;
        dest.height = animmanager.getAnim().anim_texture.height * scale;
    }
    
    animmanager.playAnim();
}

void Coin::draw() 
{
    //std::cout << "x : " << pos.x << " y : " << pos.y << " w : " << animmanager.animwidth * scale << std::endl;
#ifndef NDEBUG
    DrawRectangleLinesEx(dest, 2.f, YELLOW);
#endif
    source.x = animmanager.getFrame() * animmanager.animwidth;
    source.width = animmanager.animwidth;
    DrawTexturePro(animmanager.getAnim().anim_texture, source, dest, Vector2{}, 0.f, WHITE);
}

