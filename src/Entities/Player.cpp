#include "Player.hpp"


Player::Player(Vector2 startPos) 
{
    worldpos = startPos;
}

Player::~Player() 
{

}

void Player::controls() 
{
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;
}

void Player::move() 
{
    worldpos = Vector2Add(worldpos, Vector2Scale(Vector2Normalize(velocity), speed));
    velocity = {};
}

void Player::draw()
{
    DrawTextureV(player_tex, worldpos, WHITE); 
    DrawRectangleLines(worldpos.x, worldpos.y, player_tex.width, player_tex.height, RED);
}
