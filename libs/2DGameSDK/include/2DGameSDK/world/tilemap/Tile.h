/**
 * @file Tile.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Tile struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __TILE_H__
#define __TILE_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/material/Material.h>

namespace game {
  class Game;

  /**
   * @brief Contains all data that defines a single Tile of the Tile Map
   * 
   */
  struct GAMESDK_DLL Tile {
  public:
    int Id, TileID, X, Y, Rot;
    bool FlipX, FlipY;

    sf::Texture* Texture = nullptr;
    Material* Material = nullptr;
    sf::Sprite* Sprite = nullptr;
  };

} // namespace game

#endif