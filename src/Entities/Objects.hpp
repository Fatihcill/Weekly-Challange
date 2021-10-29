#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "raylib.h"
#include "AnimationManager.hpp"

#define G 1300
#define Rect_JUMP_SPD 750.0f
#define Rect_HOR_SPD 200.0f

typedef struct Rect // Used in Week 2
{
    Vector2 position;
    float speed;
    bool canJump;
} Rect;

typedef struct EnvItem // Used in Week 2, Week 3
{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

typedef struct Circ // Used in Week 2
{
    Vector2 position;
    int speed;
} Circ;

#endif