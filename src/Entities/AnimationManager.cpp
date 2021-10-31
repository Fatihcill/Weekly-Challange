#include "AnimationManager.hpp"

AnimationManager::AnimationManager(Animation &anim) : currentAnim(anim)
{
    setAnim(anim);
    anim_finished = false;
    animspeedcounter = 0;
    animspeedmax = 3;
}

void AnimationManager::playAnim()
{
    if (!anim_finished)
    {
        animspeedcounter++;
        if (animspeedcounter > animspeedmax)
        {
            ++frame;
            if (frame > currentAnim.max_frame)
            {
                frame = 0;
                anim_finished = true;
            }
            animspeedcounter = 0;
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

void AnimationManager::setAnim(Animation &anim) 
{
    //if (anim_finished)
    //{
        currentAnim = anim;
        startAnim();
    //}
}

AnimationManager::~AnimationManager()
{
    UnloadTexture(currentAnim.anim_texture);
}

