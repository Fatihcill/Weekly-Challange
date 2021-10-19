#include "PlatformGame.hpp"

PlatformGame::PlatformGame(StateData *state_data) : State(state_data)
{
    std::cout << "PlatformGame START" << std::endl;
    this->initVariables();
}

PlatformGame::~PlatformGame()
{
    std::cout << "PlatformGame FINISHED" << std::endl;
}

void PlatformGame::initVariables()
{
}


void PlatformGame::updateInput(const float &dt)
{

}


void PlatformGame::update(const float &dt)
{
    if (this->paused)
        return; // if the game paused. its return.

    //---------------START----------------
    this->updateInput(dt);
}

void PlatformGame::render()
{
    ClearBackground(WHITE);

    DrawRectangle(0.f, stateData->windowSettings.GetResolution().y - thickness, stateData->windowSettings.GetResolution().x, thickness, BLACK); // bottom wall
    DrawRectangle(0.f, 0.f, stateData->windowSettings.GetResolution().x, thickness, BLACK);                                                 // top wall
    DrawRectangle(75.f, stateData->windowSettings.GetResolution().y - thickness - 50.f, 50.f, 50.f, RED);                                          // player

    DrawTriangleLines((Vector2){stateData->windowSettings.GetResolution().x / 2, 160.0f},
                      (Vector2){stateData->windowSettings.GetResolution().x / 2 - 20.0f, 230.0f},
                      (Vector2){stateData->windowSettings.GetResolution().x / 2 + 20.0f, 230.0f}, DARKBLUE);

    //-------END---------
    pauseWindow.render(stateData);
}
