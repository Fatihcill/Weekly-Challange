#ifndef PLATFORMGAME_HPP
#define PLATFORMGAME_HPP

#include "State.hpp"
#include "PauseWindow.hpp"

class PlatformGame : public State
{
private:
    // setup pause
    // Functions
    void initVariables();
    PauseWindow pauseWindow;
    // custom Functions
    static const short thickness = 150;
    
public:
    PlatformGame(StateData *state_data);
    ~PlatformGame();
    // Functions
    void updateInput(const float &dt);
    void update(const float &dt);
    void render();

};

#endif