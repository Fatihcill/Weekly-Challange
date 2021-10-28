#include "Platformer.hpp"

Platformer::Platformer(StateData *state_data) : State(state_data)
{
    std::cout << "Platformer START" << std::endl;
    this->initVariables();
}

Platformer::~Platformer()
{
    UnloadRenderTexture(target); // Unload render texture
    std::cout << "Platformer FINISHED" << std::endl;
}

void Platformer::initVariables()
{
    GAMEEND = false;
    this->target = LoadRenderTexture(stateData->virtualwindow_width, stateData->virtualwindow_height);
    virtualratio = GetScreenWidth() / this->stateData->virtualwindow_height;

    cameramanager.setupCamera();
    player.position = (Vector2){300, 280};
    player.speed = 0;
    player.canJump = false;

    cameramanager.UpdateCameraCenter(Vector2{this->stateData->windowSettings.GetResolution().x / 2.f, this->stateData->windowSettings.GetResolution().y / 2.f});
}

void Platformer::updatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta)
{
    if (GAMEEND)
    {
        return;
    }

    playerrect = {player->position.x - 20, player->position.y - 40, 40, 40};
    

    if (IsKeyDown(KEY_LEFT))
      player->position.x -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_RIGHT))
        player->position.x += PLAYER_HOR_SPD * delta;
        
    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed * delta)
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed * delta;
        player->speed += G * delta;
        player->canJump = false;
    }
    else
        player->canJump = true;
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
    updatePlayer(&player, envItems, envItemsLength, dt);
    // cameramanager.UpdateCameraCenter(player.position);
}

void Platformer::draw()
{
    BeginTextureMode(target);
    ClearBackground(GRAY);
    BeginMode2D(cameramanager.worldspacecamera);

    for (int i = 0; i < envItemsLength; i++)
        DrawRectangleRec(envItems[i].rect, envItems[i].color);


    DrawRectangleRec(playerrect, ORANGE);
    DrawText(std::to_string(score).c_str(), this->stateData->virtualwindow_width / 2 - 75, this->stateData->virtualwindow_height / 2 - 150, 300, Color{255, 255, 255, 155});

 

    if (GAMEEND)
    {
        DrawText("GAME OVER", 100, this->stateData->virtualwindow_height / 2 - 50, 100, DARKPURPLE);
    }

    EndMode2D();
    EndTextureMode();
}

void Platformer::render()
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
