#ifndef PLATFORMGAME_HPP
#define PLATFORMGAME_HPP

#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager2D.hpp"
#include "Objects.hpp"

class PlatformGame : public State
{
private:
    static const int envItemsLength = 3;
    static const int enemysize = 5, enemy_radius = 15;
    int enemy_speed;
    int score = 0;
    // setup pause
    // Functions
    void initVariables();
    PauseWindow pauseWindow;
    // custom Functions
    static const short thickness = 150;
    CameraManager2D cameramanager;
    RenderTexture2D target; // This is where we'll draw all our objects.
    float virtualratio;

    Collision collisionManager;
    // player
    Player player = {0};
    Rectangle playerrect;
    void updatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);
    
    Enemy enemies[enemysize];
    EnvItem envItems[envItemsLength] = {
        {{0, 400, 800, 600}, 1, DARKGRAY},
        {{0, 0, 800, 100}, 1, DARKGRAY}};
    bool GAMEEND; 
public :
     PlatformGame(StateData *state_data);
    ~PlatformGame();
    // Functions
    void updateInput(const float &dt);
    void update(const float &dt);
    void render();
    void draw();
};

#endif