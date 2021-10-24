#include "GameState.hpp"
#include "extras/raygui.h"
#include "OrbitSimulator.hpp"
#include "PlatformGame.hpp"

void GameState::initVariables()
{
}

GameState::GameState(StateData *state_data) : State(state_data)
{
    std::cout << "GAME STARTING" << std::endl;
    this->initVariables();
}

GameState::~GameState()
{
    std::cout << "Game State Finished" << std::endl;
}

void GameState::updateInput(const float &dt)
{
}

void GameState::update(const float &dt)
{
    if (this->paused)
        return; //if the game paused. its return.

    this->updateInput(dt);
}

void GameState::draw()
{
    // Draw if you use Camera
}

void GameState::render()
{
    ClearBackground(RAYWHITE);

    if (GuiButton((Rectangle){50.f, ((this->stateData->windowSettings.GetResolution().y - 200) / 2.f), 100, 100}, "ORBITSIM"))
    {
        this->states->push(new OrbitSimulator(this->stateData));
    }
    if (GuiButton((Rectangle){250.f, ((this->stateData->windowSettings.GetResolution().y - 200) / 2.f), 100, 100}, "PLATFORM2D"))
    {
        this->states->push(new PlatformGame(this->stateData));
    }
    pauseWindow.render(stateData);
    
}