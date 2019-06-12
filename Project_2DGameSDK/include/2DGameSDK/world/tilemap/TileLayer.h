/**
 * @file TileLayer.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Tile Layer struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __TILE_LAYER_H__
#define __TILE_LAYER_H__

#include <2DGameSDK/world/tilemap/Tile.h>
#include <string>
#include <vector>

namespace game {

  /**
   * @brief Contains all data that defines a single Layer of the Tile Map
   * 
   */
  struct TileLayer {
    std::string Name;
    int Number;
    std::vector<std::vector<Tile*>> Tiles;
  };

} // namespace game

#endif