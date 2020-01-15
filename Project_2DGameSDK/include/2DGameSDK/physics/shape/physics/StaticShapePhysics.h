/**
 * @file StaticShapePhysics.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief StaticShapePhysics class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __STATIC_SHAPE_PHYSICS_H__
#define __STATIC_SHAPE_PHYSICS_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/physics/ShapePhysics.h>

namespace game {
  /**
   * @brief Shape Physics strategy for static shapes
   * 
   */
  class GAMESDK_DLL StaticShapePhysics : public ShapePhysics<StaticShapePhysics> {
  public:
    /**
     * @brief Constructs a new Static Shape Physics
     * 
     * @param friction the object friction
     * @param elasticity the object elasticity
     * @param isSensor wether the object is used as a sensor and cannot
     *        induce physical force to other objects
     */
    StaticShapePhysics(float friction, float elasticity, bool isSensor = true);

    /**
     * @brief Initializes the chipmunk shape
     * 
     * @param space the chipmunk space
     * @param body the chipmunk body
     * @param shape the chipmunk shape
     */
    virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape);

    /**
     * @brief Creates a copy of the shape physics
     * 
     * @return StaticShapePhysics* the copy
     */
    virtual StaticShapePhysics* Copy();

  protected:
    float mFriction = 0;
    float mElasticity = 0;
    bool mIsSensor = false;
  };
} // namespace game

#endif