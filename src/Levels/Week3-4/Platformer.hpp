#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager2D.hpp"
#include "CollisionManager.hpp"
#include "Player.hpp"
#include "Coin.hpp"

class Platformer : public State
{
private:
    // Functions
    void initVariables();
    // Variables
    PauseWindow pauseWindow;

    //Camera Screen Window Variables.
    CameraManager2D cameramanager;
    RenderTexture2D target; // This is where we'll draw all our objects.
    float virtualratio;

    //Collision Manager
    static const int coinlength = 3;
    int score = 0;
        
    Player player;
    std::vector<Coin*> coins;   
    std::vector<Rectangle> platformcollisions;

    Map map;     // Load the map
    Rectangle mapbnds;

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