#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Keybindings.hpp"

class Entity
{
public:
//idk what is this
    int ttc_sign(float x)
    {
        if (x < 0)
            return -1;
        else if (x < 0.0001)
            return 0;
        else
            return 1;
    }

    // Return absolute value of float
    float ttc_abs(float x)
    {
        if (x < 0.0)
            x *= -1.0;
        return x;
    }

    // Clamp value between min and max
    float ttc_clamp(float value, float min, float max)
    {
        const float res = value < min ? min : value;
        return res > max ? max : res;
    }

    Entity();
    ~Entity();
    
    void update();
    void EntityMoveUpdate(Entity *instance, const float &dt);

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
    Input control;
    Keybindings controller{};
};

#endif