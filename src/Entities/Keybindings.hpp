#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS_HPP

#include "iostream"
#include "raylib.h"

struct Input
{
    float right = 0.f;
    float left = 0.f;
    float up = 0.f;
    float down = 0.f;
    bool jump = false;
};

class Keybindings
{
private:
    /* data */
public:

    Keybindings() 
    { 
    };
    ~Keybindings(){};
    void InputUpdate(Input &input)
    {
        input.right = (float)(IsKeyDown('D') || IsKeyDown(KEY_RIGHT));
        input.left = (float)(IsKeyDown('A') || IsKeyDown(KEY_LEFT));
        input.up = (float)(IsKeyDown('W') || IsKeyDown(KEY_UP));
        input.down = (float)(IsKeyDown('S') || IsKeyDown(KEY_DOWN));

        // For jumping button needs to be toggled - allows pre-jump buffered (if held, jumps as soon as lands)
        if (IsKeyPressed(KEY_SPACE))
            input.jump = true;
        else if (IsKeyReleased(KEY_SPACE))
            input.jump = false;
    };
};
#endif