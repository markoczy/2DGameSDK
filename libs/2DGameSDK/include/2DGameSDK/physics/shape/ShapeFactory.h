/**
 * @file ShapeFactory.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief ShapeFactory class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SHAPE_FACTORY_H__
#define __SHAPE_FACTORY_H__

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/physics/DynamicShapePhysics.h>
#include <2DGameSDK/physics/shape/physics/KinematicShapePhysics.h>
#include <2DGameSDK/physics/shape/physics/ShapePhysics.h>
#include <2DGameSDK/physics/shape/physics/StaticShapePhysics.h>
#include <2DGameSDK/physics/shape/shapes/CircleShape.h>
#include <2DGameSDK/physics/shape/shapes/PolygonShape.h>
#include <2DGameSDK/physics/shape/shapes/RectangleShape.h>

namespace game {
  /**
   * @brief Factory class for all shape types
   * 
   */
  class GAMESDK_DLL ShapeFactory {
  public:
    /**
     * @brief Creates a Static Rectangle Shape
     * 
     * @param game the game
     * @param width the width
     * @param height the height
     * @param friction the friction
     * @param elasticity the elasticity
     * @param isSensor wether the object is used as a sensor and cannot
     *        induce physical force to other objects
     * @return RectangleShape<StaticShapePhysics>* the shape
     */
    static RectangleShape<StaticShapePhysics>* CreateStaticRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor = false);

    /**
     * @brief Creates a Kinematic Rectangle Shape
     * 
     * @param game the game
     * @param width the width
     * @param height the height
     * @param friction the friction
     * @param elasticity the elasticity
     * @param isSensor wether the object is used as a sensor and cannot
     *        induce physical force to other objects
     * @return RectangleShape<KinematicShapePhysics>* the shape
     */
    static RectangleShape<KinematicShapePhysics>* CreateKinematicRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor = true);

    /**
     * @brief Creates a Dynamic Rectangle Shape
     * 
     * @param game the game
     * @param width the width
     * @param height the height
     * @param mass the mass
     * @param friction the friction
     * @param elasticity the elasticity
     * @param useDensityForMass wether the mass value defines the density
     *        instead of the mass
     * @return RectangleShape<DynamicShapePhysics>* 
     */
    static RectangleShape<DynamicShapePhysics>* CreateDynamicRectangleShape(GameBase* game, float width, float height, float mass, float friction, float elasticity, bool useDensityForMass = false);

    /**
     * @brief Creates a Static Polygon Shape
     * 
     * @param game the game
     * @param vertices the polygon vertices
     * @param friction the friction
     * @param elasticity the elasticity
     * @param isSensor wether the object is used as a sensor and cannot
     *        induce physical force to other objects
     * @return PolygonShape<StaticShapePhysics>* the shape
     */
    static PolygonShape<StaticShapePhysics>* CreateStaticPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor = false);

    /**
     * @brief Creates a Kinematic Polygon Shape
     * 
     * @param game the game
     * @param vertices the polygon vertices
     * @param friction the friction
     * @param elasticity the elasticity
     * @param isSensor wether the object is used as a sensor and cannot
     *        induce physical force to other objects
     * @return PolygonShape<KinematicShapePhysics>* the shape
     */
    static PolygonShape<KinematicShapePhysics>* CreateKinematicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor = true);

    /**
     * @brief Creates a Dynamic Polygon Shape
     * 
     * @param game the game
     * @param vertices the polygon vertices
     * @param mass the mass
     * @param friction the friction
     * @param elasticity the elasticity
     * @param useDensityForMass wether the mass value defines the density
     *        instead of the mass
     * @return PolygonShape<DynamicShapePhysics>* the shape
     */
    static PolygonShape<DynamicShapePhysics>* CreateDynamicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float mass, float friction, float elasticity, bool useDensityForMass = false);

    /**
     * @brief Creates a Static Circle Shape
     * 
     * @param game the game
     * @param radius the circle radius
     * @param friction the friction
     * @param elasticity the elasticity
     * @param offset the circle center position
     * @param isSensor wether the object is used as a sensor and cannot
     *        induce physical force to other objects
     * @return CircleShape<StaticShapePhysics>* the shape
     */
    static CircleShape<StaticShapePhysics>* CreateStaticCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset = cpv(0, 0), bool isSensor = false);

    /**
     * @brief Creates a Kinematic Circle Shape
     * 
     * @param game the game
     * @param radius the circle radius
     * @param friction the friction
     * @param elasticity the elasticity
     * @param offset the circle center position
     * @param isSensor wether the object is used as a sensor and cannot
     *        induce physical force to other objects
     * @return CircleShape<KinematicShapePhysics>* the shape
     */
    static CircleShape<KinematicShapePhysics>* CreateKinematicCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset = cpv(0, 0), bool isSensor = true);

    /**
     * @brief Creates a Dynamic Circle Shape
     * 
     * @param game the game
     * @param radius the circle radius
     * @param mass the mass
     * @param friction the friction
     * @param elasticity the elasticity
     * @param offset the circle center position
     * @param useDensityForMass wether the mass value defines the density
     *        instead of the mass
     * @return CircleShape<DynamicShapePhysics>* the shape
     */
    static CircleShape<DynamicShapePhysics>* CreateDynamicCircleShape(GameBase* game, float radius, float mass, float friction, float elasticity, cpVect offset = cpv(0, 0), bool useDensityForMass = false);
  };
} // namespace game

#endif