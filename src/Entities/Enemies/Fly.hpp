#ifndef FLY_HPP
#define FLY_HPP

#include "AnimationManager.hpp"
#include "Enemy.hpp"

class Fly : public Enemy
{
private:
    AnimationManager::Animation attack, death, hit, flying;

public:
    static const int BLUE_FLY = 0, ORANGE_FLY = 1;
    Fly(int type);
    ~Fly();
    
    void enemyInit();
    void enemyUpdate(const float &dt);
    void enemyDraw();
};

#endif