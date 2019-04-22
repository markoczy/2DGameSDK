#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/material/MaterialMap.h>
#include <2DGameSDK/world/tilemap/Tilemap.h>
#include <SFML/Graphics.hpp>

namespace game {

  class GAMESDK_DLL GameWorld {
  public:
    GameWorld(Tilemap* tilemap, MaterialMap* materialMap);
    ~GameWorld();

    void Tick();
    void Render(sf::RenderTarget* target);

  private:
    Tilemap* mTilemap;
    MaterialMap* mMaterialMap;
  };

} // namespace game

#endif