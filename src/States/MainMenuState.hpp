#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.hpp"
#include "GameState.hpp"

class MainMenuState : public State
{
private:
    //GUI Button VARIABLES
    float bwidth, bheight;
    //Variables
    Texture backgroundTexture;
    //Functions
    void initVariables();
    void initFonts();

public:
    MainMenuState(StateData *state_data);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void render();
};

#endif