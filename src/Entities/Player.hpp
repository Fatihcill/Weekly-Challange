#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.hpp"

class Player
{
private:
    
    float speed{10.f};

    Vector2 velocity{};
    Texture player_tex = LoadTexture(ASSETS_PATH "player.png");
    
public:
    Player(Vector2 startPos);
    ~Player();

    //Variables
    Vector2 worldpos{};
    
    //functions
    void controls();
    void move();

    //draw
    void draw();
    
};

#endif