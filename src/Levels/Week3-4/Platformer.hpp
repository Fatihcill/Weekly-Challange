#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager2D.hpp"
#include "Player.hpp"
//#include "Objects.hpp" //included for envItems (platforms)
#include "Coin.hpp"

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
    //void collisionBlocks(Entity *instance, const float &dt);

    //custom variables

    static const int coinlength = 3;
    int score = 0;
        
    Player player;
    std::vector<Coin*> coins;

    Map map;     // Load the map
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