#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP

#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager2D.hpp"
#include "Player.hpp"
#include "Objects.hpp" //included for envItems (platforms)
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
    void collisionBlocks(Entity *instance, const float &dt);

    //custom variables
    static const int envHorizontalItemsLength = 5;
    static const int envVerticalItemsLength = 2;
    static const int coinlength = 3;
    int score = 0;
        
    Player player;
    std::vector<Coin*> coins;


    EnvItem envHorizontalItems[envHorizontalItemsLength] = {{{0, 500, 800, 600}, 1, DARKGREEN}, // bottom
                                                            {{0, 0, 800, 100}, 1, DARKGREEN},   // top
                                                            {{300, 350, 224, 32}, 1, BROWN},    // platform1
                                                            {{200, 400, 160, 32}, 1, BROWN},    // platorm2
                                                            {{400, 450, 160, 32}, 1, BROWN}};   // platform3

    EnvItem envVerticalItems[envVerticalItemsLength] = {{{700, 0, 100, 600}, 1, DARKBLUE}, // right
                                                        {{0, 0, 100, 600}, 1, DARKBLUE}};  // left

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