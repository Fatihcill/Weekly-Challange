#ifndef CAMERAMANAGER2D_HPP
#define CAMERAMANAGER2D_HPP

#include "raylib.h"
#include "raymath.h"

class CameraManager2D
{
private:
    /* data */
public:
    CameraManager2D();
    ~CameraManager2D();

    void setupCamera();
    void UpdateCameraCenterInsideMap(Vector2 playerpos, Rectangle *map, int width, int height);
    void UpdateCameraCenter(Vector2 center);
    Camera2D worldspacecamera = {0};
    Camera2D screenspacecamera = {0};
};

#endif