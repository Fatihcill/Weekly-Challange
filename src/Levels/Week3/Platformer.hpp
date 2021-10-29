#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP

#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager2D.hpp"
#include "AnimationManager.hpp"
#include "Player.hpp"

class Platformer : public State
{
private:
    // Functions
    void initVariables();
    // Variables
    PauseWindow pauseWindow;
    CameraManager2D cameramanager;
    RenderTexture2D target; // This is where we'll draw all our objects.
    float virtualratio;
    
    // custom Functions
    static const int envItemsLength = 4;

    //custom variables
    int score = 0;
    
    AnimationManager::Animation idle{LoadTexture(ASSETS_PATH "characters/herochar/herochar_idle_anim_strip_4.png"), 4};
    AnimationManager::Animation run{LoadTexture(ASSETS_PATH "characters/herochar/herochar_run_anim_strip_6.png"), 6};
    AnimationManager animmanager{idle};
    
    Player player{};

public:
    Platformer(StateData *state_data);
    ~Platformer();
    // Functions
    void updateInput(const float &dt);
    void update(const float &dt);
    void render();
    void draw();

};

#endif