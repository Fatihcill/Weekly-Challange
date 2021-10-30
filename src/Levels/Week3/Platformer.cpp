#include "Platformer.hpp"

Platformer::Platformer(StateData *state_data) : State(state_data)
{
    std::cout << "Platformer START" << std::endl;
    this->initVariables();
}

Platformer::~Platformer()
{
    std::cout << "Platformer FINISHED" << std::endl;
}

void Platformer::initVariables()
{
    this->target = LoadRenderTexture(stateData->virtualwindow_width, stateData->virtualwindow_height);
    virtualratio = GetScreenWidth() / this->stateData->virtualwindow_height;

    cameramanager.setupCamera();

    cameramanager.UpdateCameraCenter(Vector2{this->stateData->windowSettings.GetResolution().x / 2.f, this->stateData->windowSettings.GetResolution().y / 2.f});


    player.playerInit();
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

    player.playerUpdate(dt);
    collisionBlocks(&player.player, dt);
    player.playerMove(dt);
    //---------------START----------------
    this->updateInput(dt);
}

void Platformer::collisionBlocks(Entity *instance, const float &dt)
{
    /*for (int i = 0; i < envItemsLength; i++)
    {
        
        //GetCollisionRec
        if (CheckCollisionRecs(instance->entityrec, envItems[i].rect))
        {
            // instance undo movement
            instance->position.y = envItems[i].rect.y;
            instance->hitOnWall = true;
            instance->isGrounded = true;
            instance->velocity.y = 0.0f;
        }
    }*/
    for (int i = 0; i < envVerticalItemsLength; i++)
    {
        // Check Vertical platforms
        if (CheckCollisionRecs(instance->entityrec, envVerticalItems[i].rect))
        {
            instance->hitOnWall = true;
            instance->position.x -= instance->velocity.x * dt * 2.f;
            instance->velocity.x = 0.0f;
        }
    }

    for (int i = 0; i < envHorizontalItemsLength; i++)
    {
        //Check Vertical platforms
       
        //Check Horizontal platforms
        if (envHorizontalItems[i].blocking &&
            envHorizontalItems[i].rect.x <= instance->position.x &&
            envHorizontalItems[i].rect.x + envHorizontalItems[i].rect.width >= instance->position.x &&
            envHorizontalItems[i].rect.y >= instance->position.y &&
            envHorizontalItems[i].rect.y < instance->position.y + instance->velocity.y * dt)
        {
            instance->hitOnWall = true;
            instance->isGrounded = true;
            instance->velocity.y = 0.0f;
            instance->position.y = envHorizontalItems[i].rect.y;
        }
    }
}
void Platformer::render()
{
    BeginTextureMode(target);
    ClearBackground(SKYBLUE);
    BeginMode2D(cameramanager.worldspacecamera);


    DrawText(std::to_string(score).c_str(), this->stateData->virtualwindow_width / 2 - 75, this->stateData->virtualwindow_height / 2 - 150, 300, Color{255, 255, 255, 155});

    for (int i = 0; i < envVerticalItemsLength; i++)
        DrawRectangleRec(envVerticalItems[i].rect, envVerticalItems[i].color);

    for (int i = 0; i < envHorizontalItemsLength; i++)
        DrawRectangleRec(envHorizontalItems[i].rect, envHorizontalItems[i].color);
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
    DrawText(TextFormat("World resolution: %ix%i", this->stateData->virtualwindow_width, this->stateData->virtualwindow_height), 10, 40, 20, DARKGREEN);
    DrawFPS(GetScreenWidth() - 95, 10);

    //-------END---------
    pauseWindow.render(stateData);
}