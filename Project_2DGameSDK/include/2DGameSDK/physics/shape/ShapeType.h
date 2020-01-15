/**
 * @file ShapeType.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief ShapeType enum
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SHAPE_TYPE_H__
#define __SHAPE_TYPE_H__

namespace game {
  /**
   * @brief Identifies a shape type (e.g. rectangle)
   * 
   */
  enum ShapeType {
    Rectangle = 1,
    Polygon = 2,
    Circle = 3
  };
} // namespace game

#endif