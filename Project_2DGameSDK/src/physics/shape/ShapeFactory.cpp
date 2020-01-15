#include <2DGameSDK/physics/shape/ShapeFactory.h>

namespace game {
  RectangleShape<StaticShapePhysics>* ShapeFactory::CreateStaticRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor) {
    auto def = new StaticShapePhysics(friction, elasticity, isSensor);
    return new RectangleShape<StaticShapePhysics>(game, def, width, height);
  }

  RectangleShape<KinematicShapePhysics>* ShapeFactory::CreateKinematicRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor) {
    auto def = new KinematicShapePhysics(friction, elasticity, isSensor);
    return new RectangleShape<KinematicShapePhysics>(game, def, width, height);
  }

  RectangleShape<DynamicShapePhysics>* ShapeFactory::CreateDynamicRectangleShape(GameBase* game, float width, float height, float mass, float friction, float elasticity, bool useDensityForMass) {
    auto def = new DynamicShapePhysics(mass, friction, elasticity, useDensityForMass);
    return new RectangleShape<DynamicShapePhysics>(game, def, width, height);
  }

  PolygonShape<StaticShapePhysics>* ShapeFactory::CreateStaticPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor) {
    auto def = new StaticShapePhysics(friction, elasticity, isSensor);
    return new PolygonShape<StaticShapePhysics>(game, def, vertices);
  }

  PolygonShape<KinematicShapePhysics>* ShapeFactory::CreateKinematicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor) {
    auto def = new KinematicShapePhysics(friction, elasticity, isSensor);
    return new PolygonShape<KinematicShapePhysics>(game, def, vertices);
  }

  PolygonShape<DynamicShapePhysics>* ShapeFactory::CreateDynamicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float mass, float friction, float elasticity, bool useDensityForMass) {
    auto def = new DynamicShapePhysics(mass, friction, elasticity, useDensityForMass);
    return new PolygonShape<DynamicShapePhysics>(game, def, vertices);
  }

  CircleShape<StaticShapePhysics>* ShapeFactory::CreateStaticCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset, bool isSensor) {
    auto def = new StaticShapePhysics(friction, elasticity, isSensor);
    return new CircleShape<StaticShapePhysics>(game, def, radius, offset);
  }

  CircleShape<KinematicShapePhysics>* ShapeFactory::CreateKinematicCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset, bool isSensor) {
    auto def = new KinematicShapePhysics(friction, elasticity, isSensor);
    return new CircleShape<KinematicShapePhysics>(game, def, radius, offset);
  }

  CircleShape<DynamicShapePhysics>* ShapeFactory::CreateDynamicCircleShape(GameBase* game, float radius, float mass, float friction, float elasticity, cpVect offset, bool useDensityForMass) {
    auto def = new DynamicShapePhysics(mass, friction, elasticity, useDensityForMass);
    return new CircleShape<DynamicShapePhysics>(game, def, radius, offset);
  }
} // namespace game
