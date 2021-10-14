#ifndef GAME_H
#define GAME_H

#include "MainMenuState.hpp"

class Game
{
private:
    //Variables
    StateData stateData;
    float dt;
    std::stack<State *> states;

    //WindowSettings
    const short window_width{800};
    const short window_height{600};
    const short FPS{60};
    std::string title;

    //Initialization
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initStates();

public:
    //Constructors/Destructors
    Game();
    virtual ~Game();

    //Regular
    void endApplication();

    //Update
    void updateDt();
    void update();

    //Render
    void render();

    //Core
    void run();
};

#endif