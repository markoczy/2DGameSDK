/**
 * @file GameWorld.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Game World class
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/material/MaterialMap.h>
#include <2DGameSDK/world/tilemap/Tilemap.h>
#include <SFML/Graphics.hpp>

namespace game {
  /**
   * @brief Defines a Map of the Game
   * 
   */
  class GAMESDK_DLL GameWorld {
  public:
    /**
     * @brief Creates a new Game World object
     * 
     * @param tilemap The Tile representation
     * @param materialMap The Material assignment
     */
    GameWorld(Tilemap* tilemap, MaterialMap* materialMap);

    /**
     * @brief Destroys the Game World object
     * 
     */
    ~GameWorld();

    /**
     * @brief Updates all Elements of the Game World
     * 
     */
    void OnTick();

    /**
     * @brief Renders all Elements of the Game World
     * 
     * @param target The screen or texture to render on
     */
    void OnRender(sf::RenderTarget* target);

    sf::IntRect GetBounds();

  private:
    sf::IntRect mBounds;
    Tilemap* mTilemap = nullptr;
    MaterialMap* mMaterialMap = nullptr;
    sf::Texture* mTexture = nullptr;

    void loadTilemap();
  };

} // namespace game

#endif