#ifndef __SHAPE_FACTORY_H__
#define __SHAPE_FACTORY_H__

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/DynamicShapeDefinition.h>
#include <2DGameSDK/physics/shape/definitions/KinematicShapeDefinition.h>
#include <2DGameSDK/physics/shape/definitions/ShapeDefinition.h>
#include <2DGameSDK/physics/shape/definitions/StaticShapeDefinition.h>
#include <2DGameSDK/physics/shape/shapes/CircleShape.h>
#include <2DGameSDK/physics/shape/shapes/PolygonShape.h>
#include <2DGameSDK/physics/shape/shapes/RectangleShape.h>

namespace game {
  class GAMESDK_DLL ShapeFactory {
  public:
    static RectangleShape<StaticShapeDefinition>* CreateStaticRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor = false);
    static RectangleShape<KinematicShapeDefinition>* CreateKinematicRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor = true);
    static RectangleShape<DynamicShapeDefinition>* CreateDynamicRectangleShape(GameBase* game, float width, float height, float mass, float friction, float elasticity, bool useDensityForMass = false);

    static PolygonShape<StaticShapeDefinition>* CreateStaticPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor = false);
    static PolygonShape<KinematicShapeDefinition>* CreateKinematicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor = true);
    static PolygonShape<DynamicShapeDefinition>* CreateDynamicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float mass, float friction, float elasticity, bool useDensityForMass = false);

    static CircleShape<StaticShapeDefinition>* CreateStaticCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset = cpv(0, 0), bool isSensor = false);
    static CircleShape<KinematicShapeDefinition>* CreateKinematicCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset = cpv(0, 0), bool isSensor = true);
    static CircleShape<DynamicShapeDefinition>* CreateDynamicCircleShape(GameBase* game, float radius, float mass, float friction, float elasticity, cpVect offset = cpv(0, 0), bool useDensityForMass = false);
  };
} // namespace game

#endif