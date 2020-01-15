/**
 * @file ShapePhysics.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief ShapePhysics class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SHAPE_PHYSICS_H__
#define __SHAPE_PHYSICS_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <chipmunk/chipmunk.h>

/**
 * @brief Generic Shape Physics strategy
 * 
 * @tparam TDefinition the concrete type (used for copy)
 */
template <class TDefinition>
class GAMESDK_DLL ShapePhysics {
public:
  /**
   * @brief Initializes the chipmunk shape
   * 
   * @param space the chipmunk space
   * @param body the chipmunk body
   * @param shape the chipmunk shape
   */
  virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape) = 0;

  /**
   * @brief Creates a copy of the shape physics
   * 
   * @return TDefinition* the copy
   */
  virtual TDefinition* Copy() = 0;
};

#endif