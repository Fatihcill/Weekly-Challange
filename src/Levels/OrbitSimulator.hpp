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
    float rotationSpeed = 0.05f;      // General system rotation speed
    float earthOrbitRotation = 0.0f; // Rotation of earth around the Sun (years) in degrees
    float moonOrbitRotation = 0.0f;  // Rotation of moon around earth in degrees

    float earthsun_distance;
    float moonearth_distance;
public:
    OrbitSimulator(StateData *state_data);
    ~OrbitSimulator();
    //Functions
    void updateInput(const float &dt);
    void update(const float &dt);
    void draw();
    void render();

    //custom Functions
    void drawOrbit();
};

#endif