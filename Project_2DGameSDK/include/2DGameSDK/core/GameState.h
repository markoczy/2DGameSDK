/**
 * @file GameState.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Game State struct
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <2DGameSDK/scene/SceneGraph.h>
#include <2DGameSDK/world/GameWorld.h>
#include <SFML/Graphics.hpp>

namespace game {
  /**
   * @brief Contains the current State of the Game, if the State is changed,
   *        the behaviour of the Game changes as well.
   * 
   */
  struct GameState {
    /**
     * @brief The SceneGraph with all the Entities
     * 
     */
    SceneGraph* Scene;
    /**
     * @brief The GameWorld with Tilemap and MaterialMap
     * 
     */
    GameWorld* World;
  };

} // namespace game

#endif