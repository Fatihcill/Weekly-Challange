#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS_HPP

#include "raylib.h"

typedef struct
{
    float right;
    float left;
    float up;
    float down;
    bool jump;
} Input;

class Keybindings
{
private:
    /* data */
public:
    Input input = {false, false, false, false, false};
    Keybindings(/* args */);
    ~Keybindings();
    void InputUpdate(void)
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