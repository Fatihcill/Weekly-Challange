#ifndef PAUSE_H
#define PAUSE_H

#include "State.hpp"

class PauseWindow
{
public:
    void render(StateData *currentStateData);
    PauseWindow();
    ~PauseWindow();
};

#endif