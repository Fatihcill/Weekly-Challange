#pragma once
#include "raylib.h"
#include "json.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <unordered_map>

namespace Tiled
{
    class Tileset
    {
    public:
        int columns;
        std::string image;
        Texture2D texture;
        Vector2 imageSize;
        int margin;
        std::string name;
        int spacing;
        int tileCount;
        std::string tiledVersion;
        Vector2 tileSize;
        std::string Type;
        std::string version;
        int firstgid;

        Tileset(const char *filePath, int _firstgid)
        {
            // load and parse the json file
            std::ifstream file(filePath);
            auto data = nlohmann::json::parse(file);

            // load the image and set other properties
            columns = data["columns"];
            image = data["image"];
            imageSize = {data["imagewidth"], data["imageheight"]};
            margin = data["margin"];
            name = data["name"];
            spacing = data["spacing"];
            tileCount = data["tilecount"];
            tiledVersion = data["tiledversion"];
            tileSize = {data["tilewidth"], data["tileheight"]};
            Type = data["type"];
            version = data["version"];
            std::string path = "./res/";
            path += image.erase(0, 3);
            texture = LoadTexture(path.c_str());
            firstgid = _firstgid;
        }

        void Draw(int i, Vector2 pos)
        {
            i = i - firstgid;
            int x = (i % columns) * tileSize.x;
            int y = (i / columns) * tileSize.y;
            DrawTextureRec(texture, {(float)x, (float)y, tileSize.x, tileSize.y}, pos, WHITE);
        }

        ~Tileset()
        {
            UnloadTexture(texture);
        }
    };

}