#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "AnimationManager.hpp"

class Enemy
{
private:
    
protected:
    Entity enemy;

public:
    Enemy(/* args */);
    ~Enemy();

    virtual void enemyInit() = 0;
    virtual void enemyUpdate(const float &dt) = 0;
    virtual void enemyDraw() = 0;
};

#endif