#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include "raylib.h"
#include "raymath.h"

class CameraManager
{
private:
    /* data */
public:
    CameraManager();
    ~CameraManager();

    void setupCamera();
    void UpdateCameraCenterInsideMap(Vector2 playerpos, Rectangle *map, int width, int height);
    void UpdateCameraCenter(Vector2 center);
    Camera2D worldspacecamera = {0};
    Camera2D screenspacecamera = {0};
};

#endif