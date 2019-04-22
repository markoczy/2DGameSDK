#ifndef __TILE_H__
#define __TILE_H__

#include <2DGameSDK/world/material/Material.h>
#include <SFML/Graphics.hpp>

namespace game {

  struct Tile {
    int Id, Tile, X, Y, Rot;
    bool FlipX, FlipY;
    sf::Texture* Texture;
    Material* Material;
  };

} // namespace game

#endif