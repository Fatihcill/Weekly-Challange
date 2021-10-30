#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"

class Entity
{
public:
//idk what is this
    Entity();
    ~Entity();

    //Functions

    //Variables
    int width;
    int height;

    Vector2 position;
    Rectangle entityrec;
    float direction;
    float maxSpd;
    float acc;
    float dcc;
    float gravity;
    float jumpImpulse;
    float jumpRelease;
    Vector2 velocity;

    bool isGrounded;
    bool isJumping;
    // Flags for detecting collision
    bool hitOnWall;

};

#endif