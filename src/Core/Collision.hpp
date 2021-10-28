#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "math.h"
class Collision
{
private:
    
public:
    bool collisionCircleRect(float cx, float cy, float radius, float rx, float ry, float rw, float rh);
    Collision(/* args */);
    ~Collision();
};

#endif