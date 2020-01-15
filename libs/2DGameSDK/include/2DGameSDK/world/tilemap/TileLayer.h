/**
 * @file TileLayer.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Tile Layer struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2020
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
    /**
     * @brief Constructs a new Tile Layer
     * 
     * @param tileAmounts the amounts of tiles in x and y direction
     * @param tileBounds the bounds of a single tile
     * @param yOffset the offset in tiles count
     */
    TileLayer(sf::Vector2i tileAmounts, sf::Vector2i tileBounds, int yOffset = 0);

    /**
     * @brief Destroys the Tile Layer
     * 
     */
    ~TileLayer();

    /**
     * @brief Retreives the Z Index
     * 
     * @return int the Z Index
     */
    int GetZIndex();

    /**
     * @brief Retreives the layer Number
     * 
     * @return int the number
     */
    int GetNumber();

    /**
     * @brief Retreives the layer Name
     * 
     * @return std::string the name
     */
    std::string GetName();

    /**
     * @brief Sets the Z Index
     * 
     * @param zIndex the new Z Index
     */
    void SetZIndex(int zIndex);

    /**
     * @brief Sets the Number
     * 
     * @param number the new number
     */
    void SetNumber(int number);

    /**
     * @brief Sets the Name
     * 
     * @param name the new name
     */
    void SetName(std::string name);

    /**
     * @brief Sets the Tiles
     * 
     * @param tiles the new tiles
     */
    void SetTiles(std::vector<std::vector<Tile*>> tiles);
    std::vector<std::vector<Tile*>> GetTiles();

    /**
     * @brief Renders the TileLaer
     * 
     * @param target the render target
     * @param states the render states
     */
    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    /**
     * @brief Callback after texture load (creates single sprite)
     * 
     */
    void OnTexturesLoaded();

    /**
     * @brief Create a Multilayered tilelayer. Used for 2.5D Rendering
     * 
     * @return std::vector<TileLayer*> 
     */
    std::vector<TileLayer*> CreateMultilayered();

  private:
    sf::Vector2i mTileAmounts = sf::Vector2i();
    sf::Vector2i mTileBounds = sf::Vector2i();
    sf::Vector2i mTotalBounds = sf::Vector2i();
    int mYOffset = 0;
    int mZIndex = constants::DEFAULT_ZINDEX_WORLD;
    std::string mName;
    int mNumber;
    std::vector<std::vector<Tile*>> mTiles;
    sf::Texture* mTexture = nullptr;
    sf::Sprite* mSprite = nullptr;
  };

} // namespace game

#endif