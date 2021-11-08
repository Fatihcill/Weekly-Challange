#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <vector>
#include "raylib.h"
#include "Entity.hpp"

void CollisionEntityRecVec(Entity *instance, std::vector<Rectangle> *collisions, const float &dt);

#endif