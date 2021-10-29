#include "Entity.hpp"


Entity::Entity(/* args */) 
{
    
}

Entity::~Entity() 
{
    
}

void Entity::update()
{
    controller.InputUpdate(control);
}

void Entity::EntityMoveUpdate(Entity *instance, const float &dt)
{
    //GroundCheck(instance);
    instance->direction = (instance->control.right - instance->control.left);
    float deadZone = 0.0;
    if (ttc_abs(instance->direction) > deadZone)
    {
        instance->velocity.x += instance->direction * instance->acc * dt;
        instance->velocity.x = ttc_clamp(instance->velocity.x, -instance->maxSpd, instance->maxSpd);
    }
    else
    {
        // No direction means deacceleration
        float xsp = instance->velocity.x;
        if (ttc_abs(0 - xsp) < instance->dcc * dt)
            instance->velocity.x = 0;
        else if (xsp > 0)
            instance->velocity.x -= instance->dcc * dt;
        else
            instance->velocity.x += instance->dcc * dt;
    }

    if (instance->isGrounded)
    {
        if (instance->isJumping)
        {
            instance->isJumping = false;
            instance->control.jump = false; // Cancel input button
        }
        else if (!instance->isJumping && instance->control.jump)
        {
            instance->velocity.y = instance->jumpImpulse;
            instance->isJumping = true;
            instance->isGrounded = false;
        }
    }
    else
    {
        if (instance->isJumping)
        {
            if (!instance->control.jump)
            {
                instance->isJumping = false;

                if (instance->velocity.y < instance->jumpRelease)
                {
                    instance->velocity.y = instance->jumpRelease;
                }
            }
        }
    }

    // Add gravity
    instance->velocity.y += instance->gravity * dt;

    // Limit falling to negative jump value
    if (instance->velocity.y > -instance->jumpImpulse)
    {
        instance->velocity.y = -instance->jumpImpulse;
    }
    // CollisionCheck(instance);

    // Horizontal velocity together including last frame sub-pixel value
    float xVel = instance->velocity.x * dt + instance->hsp;
    // Horizontal velocity in pixel values
    //int xsp = (int)ttc_abs(xVel) * ttc_sign(xVel);
    // Save horizontal velocity sub-pixel value for next frame
    instance->hsp = instance->velocity.x * dt;
    //instance->hsp = instance->velocity.x * dt - xsp;

    // Vertical velocity together including last frame sub-pixel value
    float yVel = instance->velocity.y * dt + instance->vsp;
    // Vertical velocity in pixel values
    //int ysp = (int)ttc_abs(yVel) * ttc_sign(yVel);
    // Save Vertical velocity sub-pixel value for next frame
    instance->vsp = instance->velocity.y * dt;
    //instance->vsp = instance->velocity.y * dt - ysp;

    // Add pixel value velocity to the position
    //instance->position.x += xsp;
    //instance->position.y += ysp;
    std::cout << xVel << std::endl;
    // Prototyping Safety net - keep in view
    instance->position.x += xVel;
    //instance->position.x = ttc_clamp(instance->position.x, 0.0, TILE_MAP_WIDTH * (float)TILE_SIZE);
    //instance->position.y = ttc_clamp(instance->position.y, 0.0, TILE_MAP_HEIGHT * (float)TILE_SIZE);
}
