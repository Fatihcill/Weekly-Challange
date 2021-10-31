#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Physics2D.hpp"
#include "Keybindings.hpp"
#include "AnimationManager.hpp"
#include <cmath>

class Player
{
private:
    Input control;
    Keybindings controller{};
    //Animattion variables
    AnimationManager::Animation idle{LoadTexture(ASSETS_PATH "Week3/herochar sprites/herochar_idle_anim_strip_4.png"), 4};
    AnimationManager::Animation run{LoadTexture(ASSETS_PATH "Week3/herochar sprites/herochar_run_anim_strip_6.png"), 6};
    AnimationManager::Animation jump{LoadTexture(ASSETS_PATH "Week3/herochar sprites/herochar_jump_up_anim_strip_3.png"), 3};
    AnimationManager::Animation jumpdown{LoadTexture(ASSETS_PATH "Week3/herochar sprites/herochar_jump_down_anim_strip_3.png"), 3};
    AnimationManager::Animation push{LoadTexture(ASSETS_PATH "Week3/herochar sprites/herochar_pushing_foward_anim_strip_6.png"), 6};

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