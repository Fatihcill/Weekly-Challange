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

}

void OrbitSimulator::initVariables()
{
    sunrad = 75.f;
    earthrad = 25.f;
    moonrad = 10.f;
    earthpos = {this->stateData->windowSettings.GetResolution().x / 6.f, this->stateData->windowSettings.GetResolution().y / 2.f};
    sunpos = {this->stateData->windowSettings.GetResolution().x / 2.f, this->stateData->windowSettings.GetResolution().y / 2.f};
    moonpos = {this->stateData->windowSettings.GetResolution().x / 10.f, this->stateData->windowSettings.GetResolution().y / 2.f};
}

void OrbitSimulator::drawOrbit()
{
    DrawCircle(sunpos.x, sunpos.y, sunrad, YELLOW);                                        //Draw Sun
    DrawCircleLines(sunpos.x, sunpos.y, earthsun_distance, WHITE);                         //Earth Orbit Draw
    DrawCircle(earthpos.x, earthpos.y, earthrad, BLUE);                                    //Draw earth
    DrawCircleLines(earthpos.x, earthpos.y, moonearth_distance, WHITE);                    //Moon Orbit Draw
    DrawCircle(moonpos.x, moonpos.y, moonrad, LIGHTGRAY);                                  //Draw moon
}

void OrbitSimulator::update(const float &dt) 
{
    if (this->paused)
        return; //if the game paused. its return.
    //---------------START----------------
    this->updateInput(dt);
    earthsun_distance = Vector2Distance(earthpos, sunpos);
    moonearth_distance = Vector2Distance(moonpos, earthpos);
  
    earthOrbitRotation += (365 / 360.0f * (5.0f * rotationSpeed) * rotationSpeed);
    earthpos = Vector2{sunpos.x + earthsun_distance * cos(earthOrbitRotation), sunpos.y + earthsun_distance * sin(earthOrbitRotation)};

    moonOrbitRotation += (5.0f * rotationSpeed);
    moonpos = Vector2{earthpos.x + moonearth_distance * cos(moonOrbitRotation), earthpos.y + moonearth_distance * sin(moonOrbitRotation)};

}
void OrbitSimulator::draw()
{
    //Draw If you use Camera
}

void OrbitSimulator::render()
{
    ClearBackground(BLACK);
    this->drawOrbit();

    //-------END---------
    pauseWindow.render(stateData);
}
