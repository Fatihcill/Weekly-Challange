#include "State.hpp"

State::State(StateData *state_data)
{
    this->stateData = state_data;
    this->states = state_data->states;
    this->quit = false;
    this->paused = false;
    this->stateData->windowSettings.InitState();
    this->stateData->windowSettings.Show(false);
}

State::~State()
{
}

//Accessors
const bool &State::getQuit() const
{
    return this->quit;
}

//Functions
void State::endState()
{
    this->quit = true;
}

void State::pauseState()
{
    this->paused = true;
}

void State::unpauseState()
{
    this->paused = false;
}

void State::update(const float &dt) 
{
    std::cout << this->stateData->states->top() << std::endl;
}