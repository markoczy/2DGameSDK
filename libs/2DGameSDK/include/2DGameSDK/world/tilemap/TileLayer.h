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

#include <string>
#include <vector>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/world/tilemap/Tile.h>

namespace game {

  /**
   * @brief Contains all data that defines a single Layer of the Tile Map
   * 
   */
  class TileLayer : public VisualObject {
  public:
    TileLayer(sf::IntRect worldBounds, sf::IntRect tileBounds);
    ~TileLayer();

    int GetZIndex();

    int GetNumber();

    std::string GetName();

    void SetZIndex(int zIndex);

    void SetNumber(int number);

    void SetName(std::string name);

    void SetTiles(std::vector<std::vector<Tile*>> tiles);
    std::vector<std::vector<Tile*>> GetTiles();

    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    void OnTexturesLoaded();

  private:
    sf::IntRect mWorldBounds = sf::IntRect();
    sf::IntRect mTileBounds = sf::IntRect();
    int mZIndex = constants::DEFAULT_ZINDEX_WORLD;
    std::string mName;
    int mNumber;
    std::vector<std::vector<Tile*>> mTiles;
    sf::Texture* mTexture = nullptr;
    sf::Sprite* mSprite = nullptr;
  };

} // namespace game

#endif