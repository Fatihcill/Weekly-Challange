#include "Worm.hpp"

Worm::Worm() 
{

}

Worm::~Worm() 
{
    UnloadTexture(death.anim_texture);
    UnloadTexture(hit.anim_texture);
    UnloadTexture(walk.anim_texture);
}

void Worm::enemyInit() 
{
    
}

void Worm::enemyUpdate(const float &dt) 
{
    
}

void Worm::enemyDraw() 
{
    
}
