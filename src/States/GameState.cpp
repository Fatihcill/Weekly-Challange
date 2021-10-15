#include "GameState.hpp"
#include "extras/raygui.h"
#include "OrbitSimulator.hpp"

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

void GameState::render()
{
    ClearBackground(RAYWHITE);

    if (GuiButton((Rectangle){50.f, ((this->stateData->windowSettings.GetResolution().y - 200) / 2.f), 200, 200}, "ORBITSIM"))
    {
        this->states->push(new OrbitSimulator(this->stateData));
    }

    pauseWindow.render(stateData);
    
}

/*
void GameState::DrawSphereBasic(Color color)
{
    int rings = 16;
    int slices = 16;

    // Make sure there is enough space in the internal render batch
    // buffer to store all required vertex, batch is reseted if required
    rlCheckRenderBatchLimit((rings + 2) * slices * 6);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    for (int i = 0; i < (rings + 2); i++)
    {
        for (int j = 0; j < slices; j++)
        {
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * sinf(DEG2RAD * (j * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * i)),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * cosf(DEG2RAD * (j * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * sinf(DEG2RAD * ((j + 1) * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * cosf(DEG2RAD * ((j + 1) * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * sinf(DEG2RAD * (j * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * cosf(DEG2RAD * (j * 360 / slices)));

            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * sinf(DEG2RAD * (j * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * i)),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * cosf(DEG2RAD * (j * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i))) * sinf(DEG2RAD * ((j + 1) * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i))) * cosf(DEG2RAD * ((j + 1) * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * sinf(DEG2RAD * ((j + 1) * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * cosf(DEG2RAD * ((j + 1) * 360 / slices)));
        }
    }
    rlEnd();
}*/