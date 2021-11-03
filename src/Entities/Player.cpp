#include "Player.hpp"

Player::Player()
{
}

Player::~Player()
{
    UnloadTexture(idle.anim_texture);
    UnloadTexture(run.anim_texture);
    UnloadTexture(jump.anim_texture);
    UnloadTexture(jumpdown.anim_texture);
    UnloadTexture(push.anim_texture);
}

void Player::playerInit() 
{
    
    player.position.x = 400;
    player.position.y = 200;
    player.direction = 1.0;

    player.maxSpd = 2.f * 60;
    player.acc = 0.118164f * 60 * 60;
    player.dcc = 0.113281f * 60 * 60;
    player.gravity = 0.363281f * 60 * 60;
    player.jumpImpulse = -8.f * 60;
    player.jumpRelease = player.jumpImpulse * 0.2f;
    player.velocity = (Vector2){0.0, 0.0};

    player.width = 48;
    player.height = 48;

    player.isGrounded = false;
    player.hitOnWall= false;
    player.isJumping = false;
    rotation = 1;
    player.entityrec = Rectangle{player.position.x, player.position.y, (float)player.width, (float)player.height};
    source = Rectangle{animmanager.getFrame() * animmanager.animwidth, 0.f, animmanager.animwidth, animmanager.getAnim().anim_texture.height};
    // Assign Input instance used by player
    
}

void Player::playerUpdate(const float &dt)
{
    controller.InputUpdate(control);
    // GroundCheck(instance);
    player.direction = (control.right - control.left);
    float deadZone = 0.0;
    animmanager.setAnim(idle);
    if (std::fabs(player.direction) > deadZone)
    {

        player.velocity.x += player.direction * player.acc * dt;
        player.velocity.x = ttc_clamp(player.velocity.x, -player.maxSpd, player.maxSpd);
        animmanager.setAnim(run);
        if (player.hitOnWall)
        {
            animmanager.setAnim(push);
        }
    }
    else
    {
        // No direction means deacceleration
        float xsp = player.velocity.x;
        if (std::fabs(0 - xsp) < player.dcc * dt)
            player.velocity.x = 0;
        else if (xsp > 0)
            player.velocity.x -= player.dcc * dt;
        else
            player.velocity.x += player.dcc * dt;
    }

    if (player.isGrounded)
    {
        if (player.isJumping)
        {
            player.isJumping = false;
            control.jump = false; // Cancel input button
        }
        else if (!player.isJumping && control.jump)
        {
            player.velocity.y = player.jumpImpulse;
            player.isJumping = true;
            player.isGrounded = false;
        }
    }
    else
    {
        if (player.isJumping)
        {
            animmanager.setAnim(jump);
            if (!control.jump)
            {
                player.isJumping = false;

                if (player.velocity.y < player.jumpRelease)
                {
                    player.velocity.y = player.jumpRelease;
                }
            }
        }
        else
            animmanager.setAnim(jumpdown);
    }

    // Add gravity
    player.velocity.y += player.gravity * dt;

    // Limit falling to negative jump value
    if (player.velocity.y > -player.jumpImpulse)
    {
        player.velocity.y = -player.jumpImpulse;
    }
    // CollisionCheck(instance);

    // Horizontal velocity together including last frame sub-pixel value
    animmanager.playAnim();
}

void Player::playerMove(const float &dt) 
{

    player.position.y += player.velocity.y * dt;

    player.position.x += player.velocity.x * dt;
    player.entityrec.x = player.position.x - player.entityrec.width * 0.5f;
    player.entityrec.y = player.position.y - player.entityrec.height;

}

void Player::playerDraw() 
{
#ifndef NDEBUG
    DrawRectangleLinesEx(player.entityrec, 1.f, RED);
#endif

    if (control.right > 0.f)
    {
        if (rotation != 1)
        {
            rotation = 1;
            player.hitOnWall = false;
        }
    }
    else if (control.left > 0.f)
    {
        if (rotation != -1)
        {
            rotation = -1;
            player.hitOnWall = false;
        }
    }

    source.x = animmanager.getFrame() * animmanager.animwidth * rotation;
    source.width = animmanager.animwidth * rotation;

    DrawTexturePro(animmanager.getAnim().anim_texture, source, player.entityrec, Vector2{}, 0.f, WHITE);
}