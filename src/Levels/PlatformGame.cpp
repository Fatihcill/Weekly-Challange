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
    cameramanager.setupCamera();
    player.position = (Vector2){300, 280};
    player.speed = 0;
    player.canJump = false;

    e1 = Enemy{Vector2{1000, rand() % (375 - 249) + 250}, rand() % (500 - 399) + 400};
    e2 = Enemy{Vector2{1200, rand() % (375 - 249) + 250}, rand() % (500 - 399) + 400};
    e3 = Enemy{Vector2{1400, rand() % (375 - 249) + 250}, rand() % (500 - 399) + 400};
}

void PlatformGame::updatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta)
{
    e1.position.x -= e1.speed * delta;
    e2.position.x -= e2.speed * delta;
    e3.position.x -= e3.speed * delta;

    if (e1.position.x < -25.f)
    {
        e1 = Enemy{Vector2{800, rand() % (375 - 249) + 250}, rand() % (500 - 399) + 400};
    }
    if (e2.position.x < -25.f)
    {
        e2 = Enemy{Vector2{800, rand() % (375 - 249) + 250}, rand() % (500 - 399) + 400};
    }
    if (e3.position.x < -25.f)
    {
        e3 = Enemy{Vector2{800, rand() % (375 - 249) + 250}, rand() % (500 - 399) + 400};
    }

    /*if (IsKeyDown(KEY_LEFT))
      player->position.x -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_RIGHT))
        player->position.x += PLAYER_HOR_SPD * delta;*/
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

void PlatformGame::updateInput(const float &dt)
{

}

void PlatformGame::draw() 
{
    BeginTextureMode(target);
    ClearBackground(GRAY);
    BeginMode2D(cameramanager.worldspacecamera);
    for (int i = 0; i < envItemsLength; i++)
        DrawRectangleRec(envItems[i].rect, envItems[i].color);

    Rectangle playerRect = {player.position.x - 20, player.position.y - 40, 40, 40};
    DrawRectangleRec(playerRect, ORANGE);

    DrawCircle(e1.position.x, e1.position.y, 20.f, RED);
    DrawCircle(e2.position.x, e2.position.y, 20.f, RED);
    DrawCircle(e3.position.x, e3.position.y, 20.f, RED);

    EndMode2D();
    EndTextureMode();
}

void PlatformGame::update(const float &dt)
{
    if (this->paused)
        return; // if the game paused. its return.

    virtualratio = GetScreenWidth() / virtualScreenHeight;
    //---------------START----------------
    this->updateInput(dt);
    updatePlayer(&player, envItems, envItemsLength, dt);
    cameramanager.UpdateCameraCenter(Vector2{virtualScreenWidth / 2.f, virtualScreenHeight / 2.f});
    draw();
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
    DrawText(TextFormat("World resolution: %ix%i", virtualScreenWidth, virtualScreenHeight), 10, 40, 20, DARKGREEN);
    DrawFPS(GetScreenWidth() - 95, 10);

    //-------END---------
    pauseWindow.render(stateData);
}
