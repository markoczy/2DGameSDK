#ifndef __GAME_WORLD_FACTORY_H__
#define __GAME_WORLD_FACTORY_H__

#include <2DGameSDK/core/asset/AssetManager.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/GameWorld.h>
#include <2DGameSDK/world/tilemap/TileLayer.h>
#include <JSON/json.hpp>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

//! Remove
#include <iostream>
// #include <algorithm>

namespace game {

  class GAMESDK_DLL GameWorldFactory {
  public:
    static GameWorld* CreateGameWorld(std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix);

  private:
    static Tilemap* loadTilemap(std::string filename);
    static void loadTextures(Tilemap* tilemap, std::string prefix);
  };

} // namespace game

#endif