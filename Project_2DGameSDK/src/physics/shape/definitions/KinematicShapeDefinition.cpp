#include <2DGameSDK/physics/shape/definitions/KinematicShapeDefinition.h>

namespace game {

  KinematicShapeDefinition::KinematicShapeDefinition(Shape* shape, float friction, float elasticity, bool isSensor) : mShape(shape), mFriction(friction), mElasticity(elasticity), mIsSensor(isSensor) {}

  void KinematicShapeDefinition::InitProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mIsSensor) cpShapeSetSensor(shape, true);
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

} // namespace game
