#include "Player.hpp"

Player::Player()
{
}

Player::~Player()
{
}

void Player::playerInit() 
{
    
    player.position.x = 400.f;
    player.position.y = 300;
    player.direction = 1.0;

    player.maxSpd = 1.5625f * 60;
    player.acc = 0.118164f * 60 * 60;
    player.dcc = 0.113281f * 60 * 60;
    player.gravity = 0.363281f * 60 * 60;
    player.jumpImpulse = -6.5625f * 60;
    player.jumpRelease = player.jumpImpulse * 0.2f;
    player.velocity = (Vector2){0.0, 0.0};
    player.hsp = 0;
    player.vsp = 0;

    player.width = 32;
    player.height = 32;

    player.isGrounded = false;
    player.isJumping = false;

    // Assign Input instance used by player
    
}

void Player::playerUpdate(const float &dt)
{
    player.update();
    player.EntityMoveUpdate(&player, dt);
}

void Player::playerDraw() 
{
    DrawRectangle(player.position.x - player.width * 0.5, player.position.y - player.height + 1, player.width, player.height, RED);
}