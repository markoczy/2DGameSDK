#include <2DGameSDK/physics/shape/types/KinematicShape.h>

namespace game {

  KinematicShape::KinematicShape(ShapeType type, Game* game) : Shape(type, game) {}

  void KinematicShape::initProperties(cpSpace* space, cpBody* body, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetSensor(shape, true);
  }

} // namespace game
