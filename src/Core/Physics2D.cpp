#include "Physics2D.hpp"

int ttc_sign(float x)
{
    if (x < 0)
        return -1;
    else if (x < 0.0001)
        return 0;
    else
        return 1;
}


// Clamp value between min and max
float ttc_clamp(float value, float min, float max)
{
    const float res = value < min ? min : value;
    return res > max ? max : res;
}