#include "MainMenuState.hpp"

#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"


MainMenuState::MainMenuState(StateData *state_data) : State(state_data)
{
    this->initVariables();
    this->initFonts();
    std::cout << "MAINMENU STATE START" << std::endl;
}

MainMenuState::~MainMenuState()
{
    UnloadTexture(this->backgroundTexture);
    std::cout << "MAINMENU STATE FINISHED" << std::endl;
}

//Initializer functions
void MainMenuState::initVariables()
{
    this->backgroundTexture = LoadTexture(ASSETS_PATH "menu/background.png");
    bwidth = 100;
    bheight = 50;
}

void MainMenuState::initFonts()
{

}

void MainMenuState::updateInput(const float &dt)
{

}

void MainMenuState::updateButtons()
{
    //setup basic menu
        //New game
            //if (GuiButton((Rectangle){(this->stateData->window_width - bwidth) / 2.f, ((this->stateData->window_height - bheight) / 2.f) + (bheight * -1.5f), bwidth, bheight}, "Play"))
    
    if (GuiButton((Rectangle){(this->stateData->windowSettings.GetResolution().x - bwidth) / 2.f, ((this->stateData->windowSettings.GetResolution().y - bheight) / 2.f) + (bheight * -1.5f), bwidth, bheight}, "Play"))
    {
        this->states->push(new GameState(this->stateData));
    }
    //Settings the game
    if (GuiButton((Rectangle){(this->stateData->windowSettings.GetResolution().x - bwidth) / 2.f, ((this->stateData->windowSettings.GetResolution().y - bheight) / 2.f) + (bheight * 0), bwidth, bheight}, "Settings"))
    {
        std::cout << "GAME SETTINGS" << std::endl;
        this->stateData->windowSettings.Show(true);
    }
    //Quit the game
    if (GuiButton((Rectangle){(this->stateData->windowSettings.GetResolution().x - bwidth) / 2.f, ((this->stateData->windowSettings.GetResolution().y - bheight) / 2.f) + (bheight * 1.5f), bwidth, bheight}, "Exit"))
    {
        this->endState();
    }
    this->stateData->windowSettings.Update();
}

void MainMenuState::update(const float &dt)
{
    this->updateInput(dt);
}

void MainMenuState::render()
{
    ClearBackground(RAYWHITE);
    DrawTexturePro(this->backgroundTexture, Rectangle{0.f, 0.f, (float)this->backgroundTexture.width, (float)this->backgroundTexture.height}, Rectangle{0, 0, (float)this->stateData->windowSettings.GetResolution().x, (float)this->stateData->windowSettings.GetResolution().y}, Vector2{0, 0}, 0, WHITE);
    //DrawTexture(this->backgroundTexture, 0, 0, WHITE);
    this->updateButtons();
}
