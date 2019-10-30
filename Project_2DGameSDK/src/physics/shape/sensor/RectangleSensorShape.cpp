#include <2DGameSDK/physics/shape/sensor/RectangleSensorShape.h>

namespace game {
  RectangleSensorShape::RectangleSensorShape(Game* game, float width, float height) : RectangleShapeDefinition(game, width, height) {}

  void RectangleSensorShape::initProperties(cpSpace* space, cpBody* body, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetSensor(shape, true);
  }

} // namespace game
