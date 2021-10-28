#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "raylib.h"
#include "Collision.hpp"

#define G 1300
#define PLAYER_JUMP_SPD 750.0f
#define PLAYER_HOR_SPD 200.0f


typedef struct Player
{
    Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct EnvItem
{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

typedef struct Enemy
{
    Vector2 position;
    int speed;
} Enemy;



#endif