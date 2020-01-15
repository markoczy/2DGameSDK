/**
 * @file CollisionType.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief CollisionType enum
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __COLLSION_TYPE_H__
#define __COLLSION_TYPE_H__

namespace game {
  /**
   * @brief Identifies a chipmunk collision type. Only objects of same
   *        collision type can be collided
   * 
   */
  enum CollisionType { None = 0,
                       Default = 1 };
} // namespace game

#endif