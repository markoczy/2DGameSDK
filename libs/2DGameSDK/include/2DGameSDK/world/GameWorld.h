/**
 * @file GameWorld.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Game World class
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include <queue>
#include <vector>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/core/Game.h>
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
    GameWorld(Game* game, Tilemap* tilemap, MaterialMap* materialMap);

    /**
     * @brief Destroys the Game World object
     * 
     */
    ~GameWorld();

    /**
     * @brief Retreives the world Bounds as texture dimension
     * 
     * @return sf::IntRect the world bounds
     */
    sf::IntRect GetBounds();

  private:
    sf::IntRect mBounds;
    Game* mGame = nullptr;
    Tilemap* mTilemap = nullptr;
    MaterialMap* mMaterialMap = nullptr;

    void loadTilemap();
  };

} // namespace game

#endif