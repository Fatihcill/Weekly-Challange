#include "CollisionManager.hpp"
#include <iostream>

void CollisionEntityRecVec(Entity *instance, std::vector<Rectangle> *collisions, const float &dt) 
{
    //TODO: better collision detection
     for (Rectangle col : *collisions)
    {
        if (col.y <= instance->position.y &&
           col.y + col.height >= instance->position.y)
        {
            if (col.x >= instance->position.x &&
                col.x < instance->position.x + instance->velocity.x * dt)
            {
                instance->hitOnWall = true;
                instance->velocity.x = 0.0f;
                instance->position.x = col.x;
            }
            else if (col.x + col.width + instance->entityrec.width <= instance->position.x &&
                col.x + col.width + instance->entityrec.width > instance->position.x + instance->velocity.x * dt)
            {
                instance->hitOnWall = true;
                instance->velocity.x = 0.0f;
                instance->position.x = col.x + col.width + instance->entityrec.width;
            }
        }

        if (col.x <= instance->position.x &&
            col.x + col.width >= instance->position.x - instance->entityrec.width)
        {
            if (col.y >= instance->position.y &&
                col.y < instance->position.y + instance->velocity.y * dt)
            {
            instance->isGrounded = true;
            instance->velocity.y = 0.0f;
            instance->position.y = col.y;
            }
            else if (col.y + col.height <= instance->position.y &&
                col.y + col.height > instance->position.y + instance->velocity.y * dt)
            {
            instance->velocity.y = 0.0f;
            instance->position.y = col.y + col.height;
            }
        }
        //logs
        //std::cout << colx.width << " " << colx.height << std::endl;
        //std::cout << instance->position.x << " " << instance->position.y << std::endl;
    }
}
