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
  class GAMESDK_DLL Tile : public GameObject {
  public:
    struct Definition {
      int Id, TileID, X, Y, Rot;
      bool FlipX, FlipY;
    };

    Tile(GameBase* game, Tile::Definition defintion);
    virtual ~Tile();

    sf::Texture* GetTexture();

    Material* GetMaterial();

    Tile::Definition* GetDefinition();

    void SetTexture(sf::Texture* texture);

    void SetMaterial(Material* material);

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

  private:
    Definition mDefinition;
    sf::Texture* mTexture = nullptr;
    Material* mMaterial = nullptr;
    sf::Sprite* mSprite = nullptr;
  };

} // namespace game

#endif