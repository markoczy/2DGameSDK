/**
 * @file Pose.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Pose Template
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __POSE_H__
#define __POSE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace game {

  /**
   * @brief Defines a Pose (position + rotation)
   * 
   * @tparam T the vector type
   */
  template <class T>
  struct Pose {
    T origin;
    float angle;
  };

} // namespace game

#endif