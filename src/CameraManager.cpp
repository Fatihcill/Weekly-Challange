#include "CameraManager.hpp"

CameraManager::CameraManager(/* args */)
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::setupCamera()
{
    screenspacecamera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    screenspacecamera.rotation = 0.0f;
    screenspacecamera.zoom = 1.f;
    worldspacecamera.zoom = 1.f;
}
void CameraManager::UpdateCameraCenter(Vector2 center)
{
    screenspacecamera.target = center;
}
void CameraManager::UpdateCameraCenterInsideMap(Vector2 playerpos, Rectangle *map, int width, int height)
{
 
    screenspacecamera.target = playerpos;
    screenspacecamera.offset = (Vector2){width / 2.0f, height / 2.0f};
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    minX = fminf(map->x, minX);
    maxX = fmaxf(map->x + map->width, maxX);
    minY = fminf(map->y, minY);
    maxY = fmaxf(map->y + map->height, maxY);

    Vector2 max = GetWorldToScreen2D((Vector2){maxX, maxY}, screenspacecamera);
    Vector2 min = GetWorldToScreen2D((Vector2){minX, minY}, screenspacecamera);

    if (max.x < width)
        screenspacecamera.offset.x = width - (max.x - width / 2);
    if (max.y < height)
        screenspacecamera.offset.y = height - (max.y - height / 2);
    if (min.x > 0)
        screenspacecamera.offset.x = width / 2 - min.x;
    if (min.y > 0)
        screenspacecamera.offset.y = height / 2 - min.y;
}