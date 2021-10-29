#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Keybindings.hpp"

class Entity
{
private:
    /* data */
public:
    Entity(/* args */){};
    ~Entity(){};
    //Variables
    int width;
    int height;

    Vector2 position;
    float direction;
    float maxSpd;
    float acc;
    float dcc;
    float gravity;
    float jumpImpulse;
    float jumpRelease;
    Vector2 velocity;
    // Carry stored subpixel values
    float hsp;
    float vsp;

    bool isGrounded;
    bool isJumping;
    // Flags for detecting collision
    bool hitOnFloor;
    bool hitOnCeiling;
    bool hitOnWall;

    Input *control;
};
#endif