#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.hpp"
#include "PauseWindow.hpp"
#include "rlgl.h"

class GameState : public State
{
private:

    //setup pause
    PauseWindow pauseWindow;
    //Functions
    void initVariables();
    void initPlayers();


    Camera camera = {0};
    float rotationSpeed = 0.2f; // General system rotation speed

    float earthRotation = 0.0f;      // Rotation of earth around itself (days) in degrees
    float earthOrbitRotation = 0.0f; // Rotation of earth around the Sun (years) in degrees
    float moonRotation = 0.0f;       // Rotation of moon around itself
    float moonOrbitRotation = 0.0f;  // Rotation of moon around earth in degrees

    const float sunRadius = 4.0f;
    const float earthRadius = 0.6f;
    const float earthOrbitRadius = 8.0f;
    const float moonRadius = 0.16f;
    const float moonOrbitRadius = 1.5f;
    void DrawSphereBasic(Color color);

public:
    GameState(StateData *state_data);
    virtual ~GameState();

    //Functions
    void updateInput(const float &dt);

    void updatePlayer();

    void update(const float &dt);

    void render();
};

#endif