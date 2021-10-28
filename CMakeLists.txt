cmake_minimum_required(VERSION 3.0)
project(WEEKLY_CHALLANGE CXX)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)



add_executable(${PROJECT_NAME} 
  "src/main.cpp" 
  "src/Game.cpp"
  
  "src/Entities/CameraManager2D.cpp"  
  "src/Entities/AnimationManager.cpp"  

  "src/States/State.cpp"
  "src/States/MainMenuState.cpp"
  "src/States/GameState.cpp"
 
  "src/Levels/Week1/OrbitSimulator.cpp"
  "src/Levels/Week2/PlatformGame.cpp"
  "src/Levels/Week3/Platformer.cpp"

  "src/Settings/SettingsWindow.cpp"
  "src/Pause/PauseWindow.cpp"

  )

target_include_directories(${PROJECT_NAME}
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/States"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Entities"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Settings"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Pause"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Levels"
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT_NAME="${PROJECT_NAME}") # Set project name
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
