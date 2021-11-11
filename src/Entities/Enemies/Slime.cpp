#include "Slime.hpp"

Slime::Slime() 
{

}

Slime::~Slime() 
{
    UnloadTexture(death.anim_texture);
    UnloadTexture(hit.anim_texture);
    UnloadTexture(walk.anim_texture);
    UnloadTexture(idle.anim_texture);
}
