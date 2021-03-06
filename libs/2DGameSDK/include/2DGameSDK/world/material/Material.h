/**
 * @file Material.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Material struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>

// #include<2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/physics/StaticShapePhysics.h>

namespace game {
  template <class TDefinition>
  class Shape;

  /**
   * @brief Contains all data that defines a Material in the Game World
   * 
   */
  struct Material {
    int TileID = 0;
    int Type = 0;
    std::string Name = "";
    std::vector<Shape<StaticShapePhysics>*> Shapes = std::vector<Shape<StaticShapePhysics>*>();
  };

} // namespace game

#endif