#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <2DGameSDK/world/tilemap/TileLayer.h>
#include <vector>

namespace game {

  struct Tilemap {
    int TileWidth, TileHeight;
    int TilesWide, TilesHigh;
    std::vector<TileLayer*> Layers;
  };

} // namespace game

#endif