#include "PlatformGame.hpp"

PlatformGame::PlatformGame(StateData *state_data) : State(state_data)
{
    std::cout << "PlatformGame START" << std::endl;
    this->initVariables();

}

PlatformGame::~PlatformGame()
{
    UnloadRenderTexture(target); // Unload render texture
    std::cout << "PlatformGame FINISHED" << std::endl;
}

void PlatformGame::initVariables()
{
    GAMEEND = false;
    this->target = LoadRenderTexture(stateData->virtualwindow_width, stateData->virtualwindow_height);
    virtualratio = GetScreenWidth() / this->stateData->virtualwindow_height;

    cameramanager.setupCamera();
    player.position = (Vector2){300, 280};
    player.speed = 0;
    player.canJump = false;
    enemy_speed = 100;

    float space = this->stateData->virtualwindow_width;
    for (int i = 0; i < enemysize; i++)
    {
        enemies[i] = Circ{Vector2{space, float(rand() % (375 - 249) + 250)}, enemy_speed};
        space += 300;
    }
    cameramanager.UpdateCameraCenter(Vector2{this->stateData->windowSettings.GetResolution().x / 2.f, this->stateData->windowSettings.GetResolution().y / 2.f});
}

void PlatformGame::updatePlayer(Rect *player, EnvItem *envItemss, const float &dt)
{
    if (GAMEEND)
    {
        return;
    }

    playerrect = {player->position.x - 20, player->position.y - 40, 40, 40};
    for (int i = 0; i < enemysize; i++)
    {
        enemies[i].position.x -= enemies[i].speed * dt;

        if (CheckCollisionCircleRec(enemies[i].position, enemy_radius, playerrect))
        {
            GAMEEND = true;
        }
        
        if (enemies[i].position.x < -10)
        {
            ++score;
            enemy_speed = 100 + (5 * score);
            enemies[i].speed = enemy_speed;
            enemies[i].position = Vector2{1400, float(rand() % (375 - 249) + 250)};
        }
    }

    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -Rect_JUMP_SPD;
        player->canJump = false;
    }

    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking && CheckCollisionRecs(ei->rect, playerrect))
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed * dt;
        player->speed += G * dt;
        player->canJump = false;
    }
    else
        player->canJump = true;
}

void PlatformGame::updateInput(const float &dt)
{

}

void PlatformGame::update(const float &dt)
{
    if (this->paused)
    {
        virtualratio = GetScreenWidth() / this->stateData->virtualwindow_height;
        return; // if the game paused. its return.
    }

    //---------------START----------------
    this->updateInput(dt);
    updatePlayer(&player, envItems, dt);
    // cameramanager.UpdateCameraCenter(player.position);
}

void PlatformGame::draw()
{
    BeginTextureMode(target);
    ClearBackground(GRAY);
    BeginMode2D(cameramanager.worldspacecamera);

    for (int i = 0; i < envItemsLength; i++)
        DrawRectangleRec(envItems[i].rect, envItems[i].color);

    DrawRectangleRec(playerrect, ORANGE);
    DrawText(std::to_string(score).c_str(), this->stateData->virtualwindow_width / 2 - 75, this->stateData->virtualwindow_height / 2 - 150, 300, Color{255, 255, 255, 155});

    for (int i = 0; i < enemysize; i++)
    {
        DrawCircle(enemies[i].position.x, enemies[i].position.y, enemy_radius, RED);
    }

    if (GAMEEND)
    {
        DrawText("GAME OVER", 100, this->stateData->virtualwindow_height / 2 - 50, 100, DARKPURPLE);
    }

    EndMode2D();
    EndTextureMode();
}

void PlatformGame::render()
{
    ClearBackground(BLACK);
    BeginMode2D(cameramanager.screenspacecamera);
    DrawTexturePro(target.texture, Rectangle{0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height},
                   Rectangle{-virtualratio, -virtualratio, GetScreenWidth() + (virtualratio * 2), GetScreenHeight() + (virtualratio * 2)},
                   Vector2{0, 0}, 0.f, WHITE
                   );
    EndMode2D();

    DrawText(TextFormat("Screen resolution: %ix%i", GetScreenWidth(), GetScreenHeight()), 10, 10, 20, DARKBLUE);
    DrawText(TextFormat("World resolution: %ix%i", this->stateData->virtualwindow_width, this->stateData->virtualwindow_height), 10, 40, 20, DARKGREEN);
    DrawFPS(GetScreenWidth() - 95, 10);

    //-------END---------
    pauseWindow.render(stateData);
}
