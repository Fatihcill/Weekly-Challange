#ifndef PLATFORMGAME_HPP
#define PLATFORMGAME_HPP

#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager.hpp"

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

typedef struct Player
{
    Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct EnvItem
{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;
typedef struct Enemy
{
    Vector2 position;
    int speed;
} Enemy;
class PlatformGame : public State
{
private:
    const int virtualScreenWidth = 800;
    const int virtualScreenHeight = 600;
    static const int envItemsLength = 3;
    // setup pause
    // Functions
    void initVariables();
    PauseWindow pauseWindow;
    // custom Functions
    static const short thickness = 150;
    CameraManager cameramanager;
    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight); // This is where we'll draw all our objects.
    float virtualratio;
    
    //player
    Player player = {0};    
    void updatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);
    
    Enemy e1, e2, e3;
    EnvItem envItems[envItemsLength] = {
        {{0, 400, 800, 600}, 1, DARKGRAY},
        {{0, 0, 800, 100}, 1, DARKGRAY}};

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