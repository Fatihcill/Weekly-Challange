#ifndef ORBITSIMULATOR_H
#define ORBITSIMULATOR_H

#include "State.hpp"
#include "PauseWindow.hpp"

class OrbitSimulator : public State
{
private:
    //setup pause
    //Functions
    void initVariables();
    PauseWindow pauseWindow;
    //custom Functions

    //custom Variables
    float sunrad, earthrad, moonrad;
    Vector2 earthpos, sunpos, moonpos;
    float rotationSpeed = 0.2f;      // General system rotation speed
    float earthRotation = 0.0f;      // Rotation of earth around itself (days) in degrees
    float earthOrbitRotation = 0.0f; // Rotation of earth around the Sun (years) in degrees
    float moonRotation = 0.0f;       // Rotation of moon around itself
    float moonOrbitRotation = 0.0f;  // Rotation of moon around earth in degrees


public:
    OrbitSimulator(StateData *state_data);
    ~OrbitSimulator();
    //Functions
    void updateInput(const float &dt);
    void update(const float &dt);
    void render();

    //custom Functions
    void updateOrbit();
    void drawOrbit();
};

#endif