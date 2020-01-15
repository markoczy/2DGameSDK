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
  class GAMESDK_DLL ShapeFactory {
  public:
    static RectangleShape<StaticShapePhysics>* CreateStaticRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor = false);
    static RectangleShape<KinematicShapePhysics>* CreateKinematicRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor = true);
    static RectangleShape<DynamicShapePhysics>* CreateDynamicRectangleShape(GameBase* game, float width, float height, float mass, float friction, float elasticity, bool useDensityForMass = false);

    static PolygonShape<StaticShapePhysics>* CreateStaticPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor = false);
    static PolygonShape<KinematicShapePhysics>* CreateKinematicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor = true);
    static PolygonShape<DynamicShapePhysics>* CreateDynamicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float mass, float friction, float elasticity, bool useDensityForMass = false);

    static CircleShape<StaticShapePhysics>* CreateStaticCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset = cpv(0, 0), bool isSensor = false);
    static CircleShape<KinematicShapePhysics>* CreateKinematicCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset = cpv(0, 0), bool isSensor = true);
    static CircleShape<DynamicShapePhysics>* CreateDynamicCircleShape(GameBase* game, float radius, float mass, float friction, float elasticity, cpVect offset = cpv(0, 0), bool useDensityForMass = false);
  };
} // namespace game

#endif