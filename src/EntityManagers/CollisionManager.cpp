#include "CollisionManager.hpp"
#include <iostream>

void CollisionEntityRecVec(Entity *instance, std::vector<Rectangle> *collisions, const float &dt) 
{
    //TODO: better collision detection
     for (Rectangle col : *collisions)
    {
        Rectangle colx = GetCollisionRec(instance->entityrec, col);
        if (colx.width < colx.height)
        {
            if (instance->position.x < colx.x)
            {
                instance->hitOnWall = true;
                
                instance->velocity.x = 0.0f;
                instance->position.x -= colx.width;
                // instance->entityrec.x = instance->position.x;
            }
            // player is on the right side of the tile
            else if (instance->position.x > colx.x)
            {
                instance->hitOnWall = true;
                instance->velocity.x = 0.0f;
                instance->position.x += colx.width;
                // instance->entityrec.x = instance->position.x;
            }
        }
        else if (col.x <= instance->position.x &&
         col.x + col.width >= instance->position.x &&
          col.y >= instance->position.y &&
           col.y < instance->position.y + instance->velocity.y * dt)
        {
            instance->isGrounded = true;
            instance->velocity.y = 0.0f;
            instance->position.y = col.y;
        }
        //logs
        //std::cout << colx.width << " " << colx.height << std::endl;
        //std::cout << instance->position.x << " " << instance->position.y << std::endl;
    }
}
