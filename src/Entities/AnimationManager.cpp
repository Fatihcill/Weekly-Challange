#include "AnimationManager.hpp"

void AnimationManager::playAnim()
{

    if (!anim_finished)
    {
        ++frame;
        if (frame > currentAnim.max_frame)
        {
            frame = 0;
            anim_finished = true;
        }
    }
}

void AnimationManager::startAnim()
{
    if (anim_finished)
    {
        frame = 0;
    }
        anim_finished = false;
}
AnimationManager::AnimationManager(Animation anim)
{
    currentAnim = anim;
}

AnimationManager::~AnimationManager()
{
}
