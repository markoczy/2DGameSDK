/**
 * @file Tilemap.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Tilemap struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <2DGameSDK/world/tilemap/TileLayer.h>
#include <vector>

namespace game {

  /**
   * @brief Contains all data that defines the visual representtion of a Game 
   *        World
   * 
   */
  struct Tilemap {
    int TileWidth, TileHeight;
    int TilesWide, TilesHigh;
    std::vector<TileLayer*> Layers;
  };

} // namespace game

#endif