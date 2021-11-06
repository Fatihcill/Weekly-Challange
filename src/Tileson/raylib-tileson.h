#ifndef RAYLIB_TILESON_H_
#define RAYLIB_TILESON_H_

#include <string>
#include <vector>
#include <map>

#include "raylib.h"
#include "tileson.hpp"



class RaylibTilesonData {
    public:
        std::map<std::string, Texture> textures;
        tson::Map* map;
};


typedef struct Map {
    void* data;
} Map;

Map LoadTiledFromMemory(const unsigned char *fileData, int dataSize, const char* baseDir);
Map LoadTiled(const char* fileName);
bool IsTiledReady(Map map);
void DrawTiled(Map map, int posX, int posY, Color tint);
void UnloadMap(Map map);
std::vector<tson::Layer> GetLayers(Map map);
Rectangle RectangleFromTiledRectangle(tson::Rect rect);
// TODO: Add World support with LoadTiledWorld()


#endif  // RAYLIB_TILESON_H_
