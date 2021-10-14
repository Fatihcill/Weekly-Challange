#include "stdafx.hpp"
#include "Game.hpp"

//Constructors/Destructors
Game::Game()
{
    this->initVariables();
    //this->initGraphicsSettings();
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//Initializer functions
void Game::initVariables()
{
    this->dt = 0.f;
}

void Game::initGraphicsSettings()
{
    
}

void Game::initWindow()
{
    InitWindow(window_width, window_height, PROJECT_NAME);
    SetTargetFPS(FPS);
    SetExitKey(KEY_F4);
}

void Game::initStates()
{
    this->stateData.states = &this->states;
    this->states.push(new MainMenuState(&this->stateData));
}

//Functions
void Game::endApplication()
{
    std::cout << "Ending Application!" << std::endl;
    CloseWindow();
}

void Game::updateDt()
{
    this->dt = GetFrameTime();
}

void Game::update()
{

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
            if (this->states.empty())
            {
                EndDrawing();
                exit(0);
            }
        }
    }
    //Application end
    else
    {
        this->endApplication();
    }
}

void Game::render()
{
    BeginDrawing();

    //Render items
    if (!this->states.empty())
        this->states.top()->render();

    EndDrawing();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}