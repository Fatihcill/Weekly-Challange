#include "CameraManager2D.hpp"

CameraManager2D::CameraManager2D(/* args */)
{
}

CameraManager2D::~CameraManager2D()
{
}

void CameraManager2D::setupCamera()
{
    screenspacecamera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    screenspacecamera.rotation = 0.0f;
    screenspacecamera.zoom = 1.f; // will be 1.f
    worldspacecamera.zoom = 1.f;
}

void CameraManager2D::UpdateCameraCenterInsideMap(Vector2 *target, Rectangle *mapbounds, Vector2 center)
{
    worldspacecamera.target = *target;
    worldspacecamera.offset = (Vector2){center.x / 2.0f, center.y / 2.0f};
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;


        minX = fminf(mapbounds->x, minX);
        maxX = fmaxf(mapbounds->x + mapbounds->width, maxX);
        minY = fminf(mapbounds->y, minY);
        maxY = fmaxf(mapbounds->y + mapbounds->height, maxY);

        Vector2 max = GetWorldToScreen2D((Vector2){maxX, maxY}, worldspacecamera);
        Vector2 min = GetWorldToScreen2D((Vector2){minX, minY}, worldspacecamera);

        if (max.x < center.x)
            worldspacecamera.offset.x = center.x - (max.x - center.x / 2);
        if (max.y < center.y)
            worldspacecamera.offset.y = center.y - (max.y - center.y / 2);
        if (min.x > 0)
            worldspacecamera.offset.x = center.x / 2 - min.x;
        if (min.y > 0)
            worldspacecamera.offset.y = center.y / 2 - min.y;
}

void CameraManager2D::UpdateCameraCenter(Vector2 center)
{
    screenspacecamera.target = center;
}
