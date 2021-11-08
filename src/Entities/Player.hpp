#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Keybindings.hpp"
#include "AnimationManager.hpp"
#include <cmath>
#include <bits/stdc++.h>

class Player
{
private:
    Input control;
    Keybindings controller{};
    //Animattion variables
    AnimationManager::Animation idle{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_idle_anim_strip_4.png"), 4};
    AnimationManager::Animation run{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_run_anim_strip_6.png"), 6};
    AnimationManager::Animation jump{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_jump_up_anim_strip_3.png"), 3};
    AnimationManager::Animation jumpdown{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_jump_down_anim_strip_3.png"), 3};
    AnimationManager::Animation push{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_pushing_foward_anim_strip_6.png"), 6};

//TODO WEEK5 ANIMS
    AnimationManager::Animation jumpbeforeafter{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_before_or_after_jump_strip_2.png"), 2};
    AnimationManager::Animation death{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_death_anim_strip_8.png"), 8};
    AnimationManager::Animation attack{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_attack_anim_strip_4(new).png"), 4};
    AnimationManager::Animation hit{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_hit_anim_strip_3.png"), 3};
    AnimationManager::Animation doublejump{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_jump_double_anim_strip_3.png"), 3};
    
//EFFECTS
    //jump
    AnimationManager::Animation jumpafterdusteffect{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_after_jump_dust_anim_strip_4.png"), 4};
    AnimationManager::Animation jumpbeforedusteffect{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/herochar_before_jump_dust_anim_strip_4.png"), 4};
    //attack
    AnimationManager::Animation hitsparkle{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/hit_sparkle_anim_strip_4.png"), 4};
    AnimationManager::Animation swordattack{LoadTexture(ASSETS_PATH "Metroidvania assets 16x16/herochar sprites/sword_effect_strip_4(new).png"), 4};

public:
    Player();
    ~Player();
    AnimationManager animmanager{idle};

    void playerInit();
    void playerUpdate(const float &dt);
    void playerMove(const float &dt);
    void playerDraw();

    //Variables
    Entity player{};
    Rectangle source;
    int rotation;
};

#endif