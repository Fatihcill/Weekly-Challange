#include "MainMenuState.hpp"

#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"


MainMenuState::MainMenuState(StateData *state_data) : State(state_data)
{
    this->initVariables();
    this->initFonts();

}

MainMenuState::~MainMenuState()
{
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
    /*
    if (GuiButton((Rectangle){50, 50, bwidth, bheight}, "Play"))
    {
        std::cout << "GAME STARTING" << std::endl;
        this->states->push(new GameState(this->stateData));
    }
    //Settings the game
    if (GuiButton((Rectangle){200, 200, bwidth, bheight}, "Settings"))
    {
        std::cout << "GAME SETTINGS" << std::endl;

    }
    //Quit the game
    if (GuiButton((Rectangle){400, 400, bwidth, bheight}, "Quit"))
    {
        this->endState();
    }*/
}

void MainMenuState::update(const float &dt)
{
    this->updateInput(dt);
}

void MainMenuState::render()
{
    ClearBackground(RAYWHITE);
    DrawTexturePro(this->backgroundTexture, Rectangle{0, 0, this->backgroundTexture.width, this->backgroundTexture.height}, Rectangle{0, 0, this->stateData->windowSettings.GetResolution().x, this->stateData->windowSettings.GetResolution().y}, Vector2{0, 0}, 0, WHITE);
    //DrawTexture(this->backgroundTexture, 0, 0, WHITE);
    this->updateButtons();
}
