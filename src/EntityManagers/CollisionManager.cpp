#include "CollisionManager.hpp"
#include <iostream>

void CollisionEntityRecVec(Entity *instance, std::vector<Rectangle> *collisions, const float &dt) 
{
    //TODO: better collision detection
     for (Rectangle col : *collisions)
    {
        float borderleft = col.x + col.width + instance->entityrec.width;
        float bordertop = col.y + col.height + instance->entityrec.height;
        
        if (col.y < instance->position.y &&
           col.y + col.height > instance->position.y)
        {
            if (borderleft <= instance->position.x &&
                borderleft > instance->position.x + instance->velocity.x * dt)
            {
                instance->hitOnWall = true;
                instance->velocity.x = 0.0f;
                instance->position.x = borderleft;
            }
            else if (col.x >= instance->position.x &&
                col.x < instance->position.x + instance->velocity.x * dt)
            {
                instance->hitOnWall = true;
                instance->velocity.x = 0.0f;
                instance->position.x = col.x;
            }
        }
        
        if (col.x < instance->position.x &&
            col.x + col.width > instance->position.x - instance->entityrec.width)
        {
            if (bordertop <= instance->position.y &&
                bordertop > instance->position.y + instance->velocity.y * dt)
            {
                instance->velocity.y = 0.0f;
                instance->position.y = bordertop;
            }
            else if (col.y >= instance->position.y &&
                col.y < instance->position.y + instance->velocity.y * dt)
            {
                instance->isGrounded = true;
                instance->velocity.y = 0.0f;
                instance->position.y = col.y;
            }
        }
        //logs
        //std::cout << colx.width << " " << colx.height << std::endl;
        //std::cout << instance->position.x << " " << instance->position.y << std::endl;
    }
}
