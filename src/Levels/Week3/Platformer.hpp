#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP

#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager2D.hpp"
#include "AnimationManager.hpp"
#include "Objects.hpp"

class Platformer : public State
{
private:
    static const int envItemsLength = 3;
    int score = 0;
    
    AnimationManager::Animation idle{LoadTexture(ASSETS_PATH "characters/herochar/herochar_idle_anim_strip_4.png"), 4};
    AnimationManager::Animation run{LoadTexture(ASSETS_PATH "characters/herochar/herochar_run_anim_strip_6.png"), 6};
    AnimationManager animmanager{idle};
    // Functions
    void initVariables();
    PauseWindow pauseWindow;
    // custom Functions
    static const short thickness = 150;
    CameraManager2D cameramanager;
    RenderTexture2D target; // This is where we'll draw all our objects.
    float virtualratio;


    // player
    Player player = {0};
    Rectangle playerrect;
    void updatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);

    EnvItem envItems[envItemsLength] = {
        {{0, 400, 800, 600}, 1, DARKGRAY},
        {{0, 0, 800, 100}, 1, DARKGRAY}};
    bool GAMEEND;

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