#include <2DGameSDK/physics/shape/ShapeFactory.h>

namespace game {
  RectangleShape* ShapeFactory::CreateStaticRectangleShape(Game* game, float width, float height, float friction, float elasticity, bool isSensor) {
    auto def = new StaticShapeDefinition(friction, elasticity, isSensor);
    return new RectangleShape(game, def, width, height);
  }

  RectangleShape* ShapeFactory::CreateKinematicRectangleShape(Game* game, float width, float height, float friction, float elasticity, bool isSensor) {
    auto def = new KinematicShapeDefinition(friction, elasticity, isSensor);
    return new RectangleShape(game, def, width, height);
  }

  RectangleShape* ShapeFactory::CreateDynamicRectangleShape(Game* game, float width, float height, float mass, float friction, float elasticity, bool useDensityForMass) {
    auto def = new DynamicShapeDefinition(mass, friction, elasticity, useDensityForMass);
    return new RectangleShape(game, def, width, height);
  }

  PolygonShape* ShapeFactory::CreateStaticPolygonShape(Game* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor) {
    auto def = new StaticShapeDefinition(friction, elasticity, isSensor);
    return new PolygonShape(game, def, vertices);
  }

  PolygonShape* ShapeFactory::CreateKinematicPolygonShape(Game* game, std::vector<cpVect> vertices, float friction, float elasticity, bool isSensor) {
    auto def = new KinematicShapeDefinition(friction, elasticity, isSensor);
    return new PolygonShape(game, def, vertices);
  }

  PolygonShape* ShapeFactory::CreateDynamicPolygonShape(Game* game, std::vector<cpVect> vertices, float mass, float friction, float elasticity, bool useDensityForMass) {
    auto def = new DynamicShapeDefinition(mass, friction, elasticity, useDensityForMass);
    return new PolygonShape(game, def, vertices);
  }

  CircleShape* ShapeFactory::CreateStaticCircleShape(Game* game, float radius, float friction, float elasticity, cpVect offset, bool isSensor) {
    auto def = new StaticShapeDefinition(friction, elasticity, isSensor);
    return new CircleShape(game, def, radius, offset);
  }

  CircleShape* ShapeFactory::CreateKinematicCircleShape(Game* game, float radius, float friction, float elasticity, cpVect offset, bool isSensor) {
    auto def = new KinematicShapeDefinition(friction, elasticity, isSensor);
    return new CircleShape(game, def, radius, offset);
  }

  CircleShape* ShapeFactory::CreateDynamicCircleShape(Game* game, float radius, float mass, float friction, float elasticity, cpVect offset, bool useDensityForMass) {
    auto def = new DynamicShapeDefinition(mass, friction, elasticity, useDensityForMass);
    return new CircleShape(game, def, radius, offset);
  }
} // namespace game
