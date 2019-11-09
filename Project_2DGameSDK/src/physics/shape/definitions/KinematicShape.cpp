#include <2DGameSDK/physics/shape/definitions/KinematicShape.h>

namespace game {

  KinematicShape::KinematicShape(ShapeType type, Game* game, bool isSensor) : Shape(type, game), mIsSensor(isSensor) {}

  void KinematicShape::SetFriction(float friction) {
    mFriction = friction;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetFriction(shape, friction);
    }
  }

  void KinematicShape::SetElasticity(float elasticity) {
    mElasticity = elasticity;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetElasticity(shape, elasticity);
    }
  }

  void KinematicShape::initProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mIsSensor) cpShapeSetSensor(shape, true);
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

} // namespace game
