/**
 * @file Constants.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Constants of 2DGameSDK
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __GAMESDK_CONSTANTS_H__
#define __GAMESDK_CONSTANTS_H__

#include <SFML/Graphics.hpp>

namespace game::constants {
  /**
   * @brief Default Z Index for world elements
   * 
   */
  const int DEFAULT_ZINDEX_WORLD = 0;

  /**
   * @brief Default Z Index for Entities
   * 
   */
  const int DEFAULT_ZINDEX_ENTITY = 100;

  /**
   * @brief Default Z Index for Projectiles
   * 
   */
  const int DEFAULT_ZINDEX_PROJECTILE = 200;

  /**
   * @brief Default Z Index for Effects
   * 
   */
  const int DEFAULT_ZINDEX_EFFECT = 300;

  /**
   * @brief Default start state for animated objects
   * 
   */
  const int DEFAULT_ANIMATION_START = 0;

  /**
   * @brief The number Pi
   * 
   */
  const float PI = 3.14159265358979323846;

  /**
   * @brief The number Pi/2
   * 
   */
  const float PI_2 = 1.57079632679489661923;

  /**
   * @brief The number Pi/4
   * 
   */
  const float PI_4 = 0.785398163397448309615;

  /**
   * @brief The number Pi*2
   * 
   */
  const float PI_X_2 = 6.28318530717958647692;

  /**
   * @brief Unspecified dimension (means use default value)
   * 
   */
  const sf::Vector2f DIMENSION_USE_DEFAULT = sf::Vector2f(-1, -1);

  /**
   * @brief SFML 2D Vector (0, 0)
   */
  const sf::Vector2f SF_VEC2F_ZERO();

  /**
   * @brief SFML 3D Vector (0, 0, 0)
   */
  const sf::Vector3f SF_VEC3F_ZERO();

  /**
   * @brief Identity Matrix
   * 
   */
  const sf::Transform SF_TRANSFORM_I = sf::Transform();

} // namespace game::constants

#endif