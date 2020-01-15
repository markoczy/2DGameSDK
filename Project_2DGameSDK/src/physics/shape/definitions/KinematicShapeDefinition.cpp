#include <2DGameSDK/physics/shape/physics/KinematicShapePhysics.h>

namespace game {

  KinematicShapePhysics::KinematicShapePhysics(float friction, float elasticity, bool isSensor) : mFriction(friction), mElasticity(elasticity), mIsSensor(isSensor) {}

  void KinematicShapePhysics::InitProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mIsSensor) cpShapeSetSensor(shape, true);
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

  KinematicShapePhysics* KinematicShapePhysics::Copy() {
    return new KinematicShapePhysics(mFriction, mElasticity, mIsSensor);
  }

} // namespace game
