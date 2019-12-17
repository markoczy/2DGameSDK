#include <2DGameSDK/physics/shape/ShapeFactory.h>

namespace game {
  RectangleShape<StaticShapeDefinition>* ShapeFactory::CreateStaticRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor) {
    auto def = new StaticShapeDefinition(friction, elasticity, isSensor);
    return new RectangleShape<StaticShapeDefinition>(game, def, width, height);
  }

  RectangleShape<KinematicShapeDefinition>* ShapeFactory::CreateKinematicRectangleShape(GameBase* game, float width, float height, float friction, float elasticity, bool isSensor) {
    auto def = new KinematicShapeDefinition(friction, elasticity, isSensor);
    return new RectangleShape<KinematicShapeDefinition>(game, def, width, height);
  }

  RectangleShape<DynamicShapeDefinition>* ShapeFactory::CreateDynamicRectangleShape(GameBase* game, float width, float height, float mass, float friction, float elasticity, bool useDensityForMass) {
    auto def = new DynamicShapeDefinition(mass, friction, elasticity, useDensityForMass);
    return new RectangleShape<DynamicShapeDefinition>(game, def, width, height);
  }

  PolygonShape<StaticShapeDefinition>* ShapeFactory::CreateStaticPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor) {
    auto def = new StaticShapeDefinition(friction, elasticity, isSensor);
    return new PolygonShape<StaticShapeDefinition>(game, def, vertices);
  }

  PolygonShape<KinematicShapeDefinition>* ShapeFactory::CreateKinematicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor) {
    auto def = new KinematicShapeDefinition(friction, elasticity, isSensor);
    return new PolygonShape<KinematicShapeDefinition>(game, def, vertices);
  }

  PolygonShape<DynamicShapeDefinition>* ShapeFactory::CreateDynamicPolygonShape(GameBase* game, std::vector<cpVect> vertices, float mass, float friction, float elasticity, bool useDensityForMass) {
    auto def = new DynamicShapeDefinition(mass, friction, elasticity, useDensityForMass);
    return new PolygonShape<DynamicShapeDefinition>(game, def, vertices);
  }

  CircleShape<StaticShapeDefinition>* ShapeFactory::CreateStaticCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset, bool isSensor) {
    auto def = new StaticShapeDefinition(friction, elasticity, isSensor);
    return new CircleShape<StaticShapeDefinition>(game, def, radius, offset);
  }

  CircleShape<KinematicShapeDefinition>* ShapeFactory::CreateKinematicCircleShape(GameBase* game, float radius, float friction, float elasticity, cpVect offset, bool isSensor) {
    auto def = new KinematicShapeDefinition(friction, elasticity, isSensor);
    return new CircleShape<KinematicShapeDefinition>(game, def, radius, offset);
  }

  CircleShape<DynamicShapeDefinition>* ShapeFactory::CreateDynamicCircleShape(GameBase* game, float radius, float mass, float friction, float elasticity, cpVect offset, bool useDensityForMass) {
    auto def = new DynamicShapeDefinition(mass, friction, elasticity, useDensityForMass);
    return new CircleShape<DynamicShapeDefinition>(game, def, radius, offset);
  }
} // namespace game
