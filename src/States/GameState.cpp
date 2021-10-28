#include "GameState.hpp"
#include "extras/raygui.h"

#include "Week1/OrbitSimulator.hpp" 
#include "Week2/PlatformGame.hpp"   
#include "Week3/Platformer.hpp"     

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

    if (GuiButton((Rectangle){50.f, ((this->stateData->virtualwindow_height - 200) / 2.f), 100, 100}, "ORBITSIM \n WEEK 1"))
    {
        this->states->push(new OrbitSimulator(this->stateData));
    }
    if (GuiButton((Rectangle){250.f, ((this->stateData->virtualwindow_height - 200) / 2.f), 100, 100}, "RUNNER 2D \n WEEK 2"))
    {
        this->states->push(new PlatformGame(this->stateData));
    }
    if (GuiButton((Rectangle){450.f, ((this->stateData->virtualwindow_height - 200) / 2.f), 100, 100}, "PLATFORMER \n WEEK 3"))
    {
        this->states->push(new Platformer(this->stateData));
    }

    pauseWindow.render(stateData);
    
}