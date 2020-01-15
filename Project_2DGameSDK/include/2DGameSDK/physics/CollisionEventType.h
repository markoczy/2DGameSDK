/**
 * @file CollisionEventType.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief CollisionEventType enum
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __COLLSION_EVENT_TYPE_H__
#define __COLLSION_EVENT_TYPE_H__

namespace game {
  /**
   * @brief Identifies the type of a chipmunk collision event
   * 
   */
  enum CollisionEventType {
    Begin,
    PreSolve,
    PostSolve,
    Separate
  };
} // namespace game

#endif