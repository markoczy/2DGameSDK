/**
 * @file Constants.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Constants of 2DGameSDK
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAMESDK_CONSTANTS_H__
#define __GAMESDK_CONSTANTS_H__

#include <SFML/Graphics.hpp>

namespace game::constants {
  /**
   * @brief SFML 2D Vector (0, 0)
   */
  const sf::Vector2f SF_VEC2F_ZERO();

  /**
   * @brief SFML 3D Vector (0, 0, 0)
   */
  const sf::Vector3f SF_VEC3F_ZERO();

} // namespace game::constants

#endif