#ifndef __GAME_WORLD_FACTORY_H__
#define __GAME_WORLD_FACTORY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/GameWorld.h>
#include <JSON/json.hpp>
#include <fstream>
#include <string>

namespace game {

  class GAMESDK_DLL GameWorldFactory {
  public:
    static GameWorld* CreateGameWorld(std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix);

  private:
    Tilemap loadTilemap(std::string filename);
  };

} // namespace game

#endif