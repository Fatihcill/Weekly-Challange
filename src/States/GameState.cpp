#include "GameState.hpp"

void GameState::initVariables()
{
    camera.position = (Vector3){16.0f, 16.0f, 16.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FREE);


}



void GameState::initPlayers()
{
}

GameState::GameState(StateData *state_data) : State(state_data)
{
    std::cout << "GAME STARTING" << std::endl;
    this->initVariables();
    this->initPlayers();
}

GameState::~GameState()
{
    std::cout << "Game State Finished" << std::endl;
}

void GameState::updateInput(const float &dt)
{
}

void GameState::updatePlayer()
{
}

void GameState::update(const float &dt)
{
    if (this->paused)
        return; //if the game paused. its return.

    this->updateInput(dt);
    this->updatePlayer();

    UpdateCamera(&camera);

    earthRotation += (5.0f * rotationSpeed);
    earthOrbitRotation += (365 / 360.0f * (5.0f * rotationSpeed) * rotationSpeed);
    moonRotation += (2.0f * rotationSpeed);
    moonOrbitRotation += (8.0f * rotationSpeed);
}

void GameState::render()
{


    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    DrawSphere((Vector3){-1.0f, 0.0f, -2.0f}, 1.0f, GREEN);
    rlPushMatrix();
    rlScalef(sunRadius, sunRadius, sunRadius); // Scale Sun
    DrawSphereBasic(GOLD);                     // Draw the Sun
    rlPopMatrix();

    rlPushMatrix();
    rlRotatef(earthOrbitRotation, 0.0f, 1.0f, 0.0f); // Rotation for Earth orbit around Sun
    rlTranslatef(earthOrbitRadius, 0.0f, 0.0f);      // Translation for Earth orbit

    rlPushMatrix();
    rlRotatef(earthRotation, 0.25, 1.0, 0.0);        // Rotation for Earth itself
    rlScalef(earthRadius, earthRadius, earthRadius); // Scale Earth

    DrawSphereBasic(BLUE); // Draw the Earth
    rlPopMatrix();

    rlRotatef(moonOrbitRotation, 0.0f, 1.0f, 0.0f); // Rotation for Moon orbit around Earth
    rlTranslatef(moonOrbitRadius, 0.0f, 0.0f);      // Translation for Moon orbit
    rlRotatef(moonRotation, 0.0f, 1.0f, 0.0f);      // Rotation for Moon itself
    rlScalef(moonRadius, moonRadius, moonRadius);   // Scale Moon

    DrawSphereBasic(LIGHTGRAY); // Draw the Moon
    rlPopMatrix();

    // Some reference elements (not affected by previous matrix transformations)
    DrawCircle3D((Vector3){0.0f, 0.0f, 0.0f}, earthOrbitRadius, (Vector3){1, 0, 0}, 90.0f, Fade(RED, 0.5f));
    DrawGrid(20, 1.0f);

    EndMode3D();
    pauseWindow.render(stateData);
}

void GameState::DrawSphereBasic(Color color)
{
    int rings = 16;
    int slices = 16;

    // Make sure there is enough space in the internal render batch
    // buffer to store all required vertex, batch is reseted if required
    rlCheckRenderBatchLimit((rings + 2) * slices * 6);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    for (int i = 0; i < (rings + 2); i++)
    {
        for (int j = 0; j < slices; j++)
        {
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * sinf(DEG2RAD * (j * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * i)),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * cosf(DEG2RAD * (j * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * sinf(DEG2RAD * ((j + 1) * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * cosf(DEG2RAD * ((j + 1) * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * sinf(DEG2RAD * (j * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * cosf(DEG2RAD * (j * 360 / slices)));

            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * sinf(DEG2RAD * (j * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * i)),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * i)) * cosf(DEG2RAD * (j * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i))) * sinf(DEG2RAD * ((j + 1) * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i))) * cosf(DEG2RAD * ((j + 1) * 360 / slices)));
            rlVertex3f(cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * sinf(DEG2RAD * ((j + 1) * 360 / slices)),
                       sinf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))),
                       cosf(DEG2RAD * (270 + (180 / (rings + 1)) * (i + 1))) * cosf(DEG2RAD * ((j + 1) * 360 / slices)));
        }
    }
    rlEnd();
}