#include <2DGameSDK/physics/shape/types/KinematicShape.h>

namespace game {

  KinematicShape::KinematicShape(ShapeType type, Game* game, bool isSensor) : Shape(type, game), mIsSensor(isSensor) {}

  void KinematicShape::initProperties(cpSpace* space, cpBody* body, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mIsSensor) cpShapeSetSensor(shape, true);
  }

} // namespace game
