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
    screenspacecamera.zoom = 1.f;
    worldspacecamera.zoom = 1.f;
}
void CameraManager2D::UpdateCameraCenter(Vector2 center)
{
    screenspacecamera.target = center;
}