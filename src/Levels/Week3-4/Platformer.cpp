#include "Platformer.hpp"

Platformer::Platformer(StateData *state_data) : State(state_data)
{
    std::cout << "Platformer START" << std::endl;
    
    //NOTE we need change virtual window res for this app.
    stateData->virtualwindow_width = 240;
    stateData->virtualwindow_height = 160;
       
    this->initVariables();
}

Platformer::~Platformer()
{
    std::cout << "Platformer FINISHED" << std::endl;
    
    stateData->virtualwindow_width = 800;
    stateData->virtualwindow_height = 600;
    UnloadMap(map);
}

void Platformer::initVariables()
{
    this->target = LoadRenderTexture(stateData->virtualwindow_width, stateData->virtualwindow_height);
    virtualratio = GetScreenWidth() / this->stateData->virtualwindow_height;

    cameramanager.setupCamera();
    cameramanager.UpdateCameraCenter(Vector2{this->stateData->windowSettings.GetResolution().x / 2.f, this->stateData->windowSettings.GetResolution().y / 2.f});

    player.playerInit();

    //SETUP MAP-------------------------
    map = LoadTiled(ASSETS_PATH "Metroidvania assets 16x16/map/map.json");
    mapbnds = GetMapBounds(map);

    for (tson::Layer layer : GetLayersFromMap(map))
    {
        std::cout << layer.getName() << std::endl;
        
        if (layer.getName() == "player")
        {
            for(auto &obj : layer.getObjects()) 
            {
                  auto pos = obj.getPosition();
                  player.player.position = Vector2{pos.x, pos.y};
            }       
        }
       else if (layer.getName() == "coin")
        {
            for(auto &obj : layer.getObjects()) 
            {
                auto pos = obj.getPosition();
                coins.emplace_back(new Coin(pos.x, pos.y));
            }       
        }
    }
    
    for(auto &obj :  GetLayerFromMap(map, "collisions")->getObjects()) 
    {
        platformcollisions.push_back(LayerObjectRectToRaylibRect(obj));
    }
    //--------------------------------------
}

void Platformer::updateInput(const float &dt)
{
}

void Platformer::update(const float &dt)
{
    if (this->paused)
    {
        virtualratio = GetScreenWidth() / this->stateData->virtualwindow_height;
        return; // if the game paused. its return.
    }
    //---------------START----------------
    this->updateInput(dt);

    //players
    player.playerUpdate(dt); // player inputs
    CollisionEntityRecVec(&player.player, &platformcollisions, dt); // check collisions
    player.playerMove(dt);  //apply move player

    if (player.player.position.y > mapbnds.height)
    {
            this->endState();            //end game 
    }
    

    //coins update 
    if (!coins.empty())
    {
        for (int i = 0; i < coins.size(); i++)
        {
            coins[i]->update(player.player);
            if (coins[i]->hasTaken && coins[i]->animmanager.anim_finished)
            {
                ++score;
                delete coins[i];
                coins.erase(coins.begin() + i);
            }
        }
    }



    cameramanager.UpdateCameraCenterInsideMap(&player.player.position, &mapbnds, Vector2{this->stateData->virtualwindow_width, this->stateData->virtualwindow_height});
}

void Platformer::render()
{
    BeginTextureMode(target);
    ClearBackground(SKYBLUE);
    BeginMode2D(cameramanager.worldspacecamera);

    //DRAW MAP ----------------
    DrawTiled(map, 0, 0, WHITE);
#ifndef NDEBUG
    for (Rectangle platform: platformcollisions)
    {
        DrawRectangleLinesEx(platform, 1.f, GREEN);
    }
#endif    
    //--------------------------
    for (auto *coin : coins)
    {
        coin->draw();
    }
     
    player.playerDraw();

    EndMode2D();
    EndTextureMode();
}

void Platformer::draw()
{
    ClearBackground(BLACK);
    BeginMode2D(cameramanager.screenspacecamera);
    DrawTexturePro(target.texture, Rectangle{0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height},
                   Rectangle{-virtualratio, -virtualratio, GetScreenWidth() + (virtualratio * 2), GetScreenHeight() + (virtualratio * 2)},
                   Vector2{0, 0}, 0.f, WHITE);
    EndMode2D();

    DrawText(TextFormat("Screen resolution: %ix%i", GetScreenWidth(), GetScreenHeight()), 10, 10, 20, DARKBLUE);
    DrawText(TextFormat("World resolution: %ix%i", this->stateData->virtualwindow_width, this->stateData->virtualwindow_height), 10, 40, 20, RED);
    DrawText(TextFormat("Score: %i", score), 75, 75, 20, BLACK);
    DrawFPS(GetScreenWidth() - 95, 10);

    //-------END---------
    pauseWindow.render(stateData);
}