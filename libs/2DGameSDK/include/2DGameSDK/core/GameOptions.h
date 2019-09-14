/**
 * @file GameOptions.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Game Options struct
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAME_OPTIONS_H__
#define __GAME_OPTIONS_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/System.hpp>

namespace game {

  /**
   * @brief Contains all Configurations of the game, as opposed to the 
   *        GameState the options are not meant to influence the behaviour
   *        of the Game (i.e. the Game Loop).
   * 
   */
  struct GameOptions {
    /**
     * @brief Title of the Game, affects Window Title
     * 
     */
    std::string Title;
    /**
     * @brief Screen Dimensions
     * 
     */
    sf::Vector2i ScreenDim;
    /**
     * @brief Zoom at start
     * 
     */
    float InitialZoom = 1;
    /**
     * @brief Framerate in 1/s
     * 
     */
    int FramesPerSecond = 50;
    /**
     * @brief Wether to render the Axis Aligned Bounding Boxes
     */
    bool RenderAABB = false;
    /**
     * @brief Wether to render the Collision Masks
     */
    bool RenderCollisionMask = false;
  };

  //   GAMESDK_DLL GameOptions DefaultOptions = GameOptions{
  //       "Game", sf::Vector2i(800, 600), 50};

} // namespace game

#endif