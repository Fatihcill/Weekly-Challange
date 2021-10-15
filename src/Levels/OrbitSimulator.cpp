#include "OrbitSimulator.hpp"
#include "rlgl.h"

OrbitSimulator::OrbitSimulator(StateData *state_data): State(state_data)
{
    std::cout << "ORBITSIMULATOR START" << std::endl;
    this->initVariables();
}

OrbitSimulator::~OrbitSimulator()
{
    std::cout << "ORBITSIMULATOR FINISHED" << std::endl;
}

void OrbitSimulator::updateInput(const float &dt)
{
    earthRotation += (5.0f * rotationSpeed);
    earthOrbitRotation += (365 / 360.0f * (5.0f * rotationSpeed) * rotationSpeed);
    moonRotation += (2.0f * rotationSpeed);
    moonOrbitRotation += (8.0f * rotationSpeed);

    earthpos = {this->stateData->windowSettings.GetResolution().x / 4, this->stateData->windowSettings.GetResolution().y / 2};
}

void OrbitSimulator::initVariables()
{
    sunrad = 100.f;
    earthrad = 40.f;
    moonrad = 10.f;
}


void OrbitSimulator::updateOrbit()
{

}

void OrbitSimulator::drawOrbit()
{
    DrawEllipse(this->stateData->windowSettings.GetResolution().x / 2, this->stateData->windowSettings.GetResolution().y / 2, sunrad / 1.1f, sunrad, YELLOW); //Draw Sun

    DrawEllipse(earthpos.x, earthpos.y, earthrad / 1.1f, earthrad, BLUE); //Draw earth

    DrawEllipse(this->stateData->windowSettings.GetResolution().x / 6, this->stateData->windowSettings.GetResolution().y / 2, moonrad / 1.1f, moonrad, LIGHTGRAY); //Draw moon
}

void OrbitSimulator::update(const float &dt) 
{
    if (this->paused)
        return; //if the game paused. its return.
    //---------------START----------------

    this->updateInput(dt);
    this->updateOrbit();
}

void OrbitSimulator::render()
{
    ClearBackground(BLACK);
    this->drawOrbit();

    //-------END---------
    pauseWindow.render(stateData);
}
