#include <2DGameSDK/physics/shape/definitions/KinematicShapeDefinition.h>

namespace game {

  KinematicShapeDefinition::KinematicShapeDefinition(float friction, float elasticity, bool isSensor) : mFriction(friction), mElasticity(elasticity), mIsSensor(isSensor) {}

  void KinematicShapeDefinition::InitProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mIsSensor) cpShapeSetSensor(shape, true);
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

  KinematicShapeDefinition* KinematicShapeDefinition::Copy() {
    return new KinematicShapeDefinition(mFriction, mElasticity, mIsSensor);
  }

} // namespace game
