#include <2DGameSDK/physics/shape/sensor/PolygonSensorShape.h>

namespace game {

  PolygonSensorShape::PolygonSensorShape(Game* game, std::vector<cpVect> vertices) : PolygonShapeDefinition(game, vertices) {
  }

  void PolygonSensorShape::initProperties(cpSpace* space, cpBody* body, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetSensor(shape, true);
  }
} // namespace game
