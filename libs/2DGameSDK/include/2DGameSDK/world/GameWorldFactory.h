#ifndef __GAME_WORLD_FACTORY_H__
#define __GAME_WORLD_FACTORY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/GameWorld.h>
#include <string>

namespace game {

  class GAMESDK_DLL GameWorldFactory {
  public:
    static GameWorld* CreateGameWorld(std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix);
  };

} // namespace game

#endif