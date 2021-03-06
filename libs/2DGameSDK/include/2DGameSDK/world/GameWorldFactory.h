/**
 * @file GameWorldFactory.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Game World Factory class
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __GAME_WORLD_FACTORY_H__
#define __GAME_WORLD_FACTORY_H__

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include <JSON/json.hpp>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/core/asset/AssetManager.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeFactory.h>
#include <2DGameSDK/physics/shape/physics/StaticShapePhysics.h>
#include <2DGameSDK/physics/shape/shapes/CircleShape.h>
#include <2DGameSDK/physics/shape/shapes/PolygonShape.h>
#include <2DGameSDK/physics/shape/shapes/RectangleShape.h>
#include <2DGameSDK/world/GameWorld.h>
#include <2DGameSDK/world/material/Material.h>
#include <2DGameSDK/world/material/MaterialMap.h>
#include <2DGameSDK/world/tilemap/TileLayer.h>

//! Remove
#include <iostream>
// #include <algorithm>

namespace game {
  /**
   * @brief Factory to create a Game World
   * 
   */
  class GAMESDK_DLL GameWorldFactory {
  public:
    /**
     * @brief Creates a Game World object
     * 
     * @param tilemapFile The path to the Tilemap
     * @param materialMapFile The path to the Material Map
     * @param texturesPrefix The prefix to find textures (Asset Manager)
     * @return GameWorld* The new Game World
     */
    static GameWorld* CreateGameWorld(Game* game, std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix, int pad = 2);

  private:
    /**
     * @brief Loads the tilemap from a file
     * 
     * @param game the game
     * @param filename The path to the file
     * @return Tilemap* The created Tilemap
     */
    static Tilemap* loadTilemap(Game* game, std::string filename);

    /**
     * @brief Loads the material map from a file
     * 
     * @param game the game
     * @param filename the path to the file
     * @return MaterialMap* the material map
     */
    static MaterialMap* loadMaterialMap(Game* game, std::string filename);

    /**
     * @brief Loads the textures for a given Tilemap the textures are stored
     *        directly in the Tile.
     * 
     * @param tilemap The Tilemap
     * @param prefix The textures prefix
     */
    static void loadTextures(Tilemap* tilemap, std::string prefix, int pad = 2);

    /**
     * @brief Load the materials once the material map is parsed
     * 
     * @param game the game
     * @param tilemap the tilemap
     * @param materialMap the materialmap
     */
    static void loadMaterials(Game* game, Tilemap* tilemap, MaterialMap* materialMap);
  };

} // namespace game

#endif