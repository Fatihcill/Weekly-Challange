#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.hpp"
#include "PauseWindow.hpp"

class GameState : public State
{
private:
    //setup pause
    PauseWindow pauseWindow;
    //Functions
    void initVariables();
public:
    GameState(StateData *state_data);
    virtual ~GameState();
    //Functions
    void updateInput(const float &dt);
    void update(const float &dt);
    void render();
};

#endif