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

  const float PI = 3.14159265358979323846;
  const float PI_2 = 1.57079632679489661923;
  const float PI_4 = 0.785398163397448309615;

  const float DEG_TO_RAD = PI / 180;
  const float RAD_TO_DEG = 180 / PI;

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