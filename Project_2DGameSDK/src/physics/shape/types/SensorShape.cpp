#include <2DGameSDK/physics/shape/types/SensorShape.h>

namespace game {

  SensorShape::SensorShape(ShapeType type, Game* game) : Shape(type, game) {}

  void SensorShape::initProperties(cpSpace* space, cpBody* body, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetSensor(shape, true);
  }

} // namespace game
