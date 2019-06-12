/**
 * @file Tile.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Tile struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __TILE_H__
#define __TILE_H__

#include <2DGameSDK/world/material/Material.h>
#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @brief Contains all data that defines a single Tile of the Tile Map
   * 
   */
  struct Tile {
    int Id, Tile, X, Y, Rot;
    bool FlipX, FlipY;
    sf::Texture* Texture;
    Material* Material;
  };

} // namespace game

#endif