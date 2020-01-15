/**
 * @file ObjectType.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief ObjectType enum
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __OBJECT_TYPE_H__
#define __OBJECT_TYPE_H__

namespace game {
  /**
   * @brief Identification of the Object Type
   * 
   */
  enum class ObjectType {
    Unknown = 0,
    Tile = 1,
    Entity = 2,
    Projectile = 3,
    Effect = 4
  };
} // namespace game

#endif