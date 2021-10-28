#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include "raylib.h"

class AnimationManager
{
public:
    struct Animation
    {
        Texture2D anim_texture;
        int max_frame;
    };
    
    AnimationManager(Animation anim);
    ~AnimationManager();

    bool anim_finished{false};
    
    void playAnim();
    void startAnim();

    //gets sets
    int getFrame(){return frame;}
    void setAnim(Animation anim){currentAnim = anim; startAnim();};
    Animation getAnim(){return currentAnim;};

private:
    Animation currentAnim{};
    int frame{};
};

#endif