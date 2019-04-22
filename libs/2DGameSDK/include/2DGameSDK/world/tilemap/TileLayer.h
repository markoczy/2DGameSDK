#ifndef __TILE_LAYER_H__
#define __TILE_LAYER_H__

#include <2DGameSDK/world/tilemap/Tile.h>
#include <string>
#include <vector>

namespace game {

  struct TileLayer {
    std::string Name;
    std::vector<std::vector<Tile>> Tiles;
  };

} // namespace game

#endif