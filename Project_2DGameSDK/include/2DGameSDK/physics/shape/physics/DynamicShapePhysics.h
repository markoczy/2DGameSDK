/**
 * @file DynamicShapePhysics.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief DynamicShapePhysics class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __DYNAMIC_SHAPE_PHYSICS_H__
#define __DYNAMIC_SHAPE_PHYSICS_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/physics/ShapePhysics.h>

namespace game {
  /**
   * @brief Shape Physics strategy for dynamic shapes
   * 
   */
  class GAMESDK_DLL DynamicShapePhysics : public ShapePhysics<DynamicShapePhysics> {
  public:
    /**
     * @brief Constructs a new Dynamic Shape Physics
     * 
     * @param mass the object mass
     * @param friction the object friction
     * @param elasticity the object elasticity
     * @param useDensityForMass wether the mass value defines the density
     *        instead of the mass
     */
    DynamicShapePhysics(float mass, float friction, float elasticity, bool useDensityForMass = false);

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
     * @return DynamicShapePhysics* the copy
     */
    virtual DynamicShapePhysics* Copy();

  protected:
    float mMass = 0;
    float mFriction = 0;
    float mElasticity = 0;
    bool mUseDensity = false;
  };
} // namespace game

#endif