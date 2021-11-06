#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP


#include "TileLoader.hpp"
#include "State.hpp"
#include "PauseWindow.hpp"
#include "CameraManager2D.hpp"
#include "Player.hpp"
//#include "Objects.hpp" //included for envItems (platforms)
#include "Coin.hpp"
#include "TileLoader.hpp"

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
    Tiled::Tileset map{ASSETS_PATH "Metroidvania assets 16x16/map/map.json", 0};
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