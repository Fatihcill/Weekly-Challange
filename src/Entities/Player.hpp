#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player
{
private:
    /* data */
public:
    Entity player{};
    Player();
    ~Player();

    void playerInit();
    void playerUpdate();
    void playerDraw();
};

#endif