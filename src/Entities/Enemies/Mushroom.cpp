#include "Mushroom.hpp"

Mushroom::Mushroom() 
{

}

Mushroom::~Mushroom() 
{
    UnloadTexture(crushed.anim_texture);
    UnloadTexture(death.anim_texture);
    UnloadTexture(hit.anim_texture);
    UnloadTexture(walk.anim_texture);
    UnloadTexture(idle.anim_texture);
}
