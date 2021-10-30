#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Physics2D.hpp"
#include "Keybindings.hpp"

class Player
{
private:
    Input control;
    Keybindings controller{};

public:
    Entity player{};
    Player();
    ~Player();

    void playerInit();
    void playerUpdate(const float &dt);
    void playerMove(const float &dt);
    void playerDraw();
};

#endif