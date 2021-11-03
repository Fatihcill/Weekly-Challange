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

    coins.emplace_back(new Coin(450, 400));
    coins.emplace_back(new Coin(500, 400));
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

    player.playerMove(dt);
    //---------------START----------------
    this->updateInput(dt);
}

void Platformer::collisionBlocks(Entity *instance, const float &dt)
{
    for (int i = 0; i < envVerticalItemsLength; i++)
    {
        Rectangle col = GetCollisionRec(instance->entityrec, envVerticalItems[i].rect);

        if (col.width < col.height)
        {
            if (instance->position.x < envVerticalItems[i].rect.x)
            {
                instance->hitOnWall = true;
                
                instance->velocity.x = 0.0f;
                instance->position.x -= col.width;
                // instance->entityrec.x = instance->position.x;
            }
            // player is on the right side of the tile
            else if (instance->position.x > envVerticalItems[i].rect.x)
            {
                instance->hitOnWall = true;
                instance->velocity.x = 0.0f;
                instance->position.x += col.width;
                // instance->entityrec.x = instance->position.x;
            }
        }

    }

    for (int i = 0; i < envHorizontalItemsLength; i++)
    {       
        if (envHorizontalItems[i].blocking &&
            envHorizontalItems[i].rect.x <= instance->position.x &&
            envHorizontalItems[i].rect.x + envHorizontalItems[i].rect.width >= instance->position.x &&
            envHorizontalItems[i].rect.y >= instance->position.y &&
            envHorizontalItems[i].rect.y < instance->position.y + instance->velocity.y * dt)
        {
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


    for (int i = 0; i < envVerticalItemsLength; i++)
        DrawRectangleRec(envVerticalItems[i].rect, envVerticalItems[i].color);

    for (int i = 0; i < envHorizontalItemsLength; i++)
        DrawRectangleRec(envHorizontalItems[i].rect, envHorizontalItems[i].color);

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