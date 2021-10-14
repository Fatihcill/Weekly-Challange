#ifndef STATE_H
#define STATE_H

#include "stdafx.hpp"
#include "SettingsWindow.hpp"

class State;

class StateData
{
public:
    //Variables
    std::stack<State *> *states;
    //short window_width;
    //short window_height;
    raysettings::SettingsWindow windowSettings{};
};

class State
{
private:
protected:
    StateData *stateData;
    std::stack<State *> *states;
    bool quit;

    //Resources
    std::vector<Texture> textures;



public:
    State(StateData *state_data);
    virtual ~State();
    
    bool paused;

    //Accessors
    const bool &getQuit() const;

    //Functions
    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateInput(const float &dt) = 0;
    virtual void update(const float &dt);
    virtual void render() = 0;
};

#endif