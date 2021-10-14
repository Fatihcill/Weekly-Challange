#include "GameState.hpp"

void GameState::initVariables()
{
}

void GameState::initFonts()
{
}

void GameState::initPlayers()
{
}

GameState::GameState(StateData *state_data) : State(state_data)
{
    std::cout << "GAME STARTING" << std::endl;
    this->initVariables();
    this->initFonts();
    this->initPlayers();
}

GameState::~GameState()
{
    std::cout << "Game State Finished" << std::endl;
}

void GameState::updateInput(const float &dt)
{
    player.controls();
}

void GameState::updatePlayer()
{
    player.move();
}

void GameState::update(const float &dt)
{
    if (this->paused)
        return; //if the game paused. its return.

    this->updateInput(dt);
    this->updatePlayer();
}

void GameState::render()
{
    ClearBackground(GRAY);

    //draw player
    player.draw();
    pauseWindow.render(stateData);
}