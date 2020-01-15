#include <2DGameSDK/physics/shape/physics/StaticShapePhysics.h>

namespace game {

  StaticShapePhysics::StaticShapePhysics(float friction, float elasticity, bool isSensor) : mFriction(friction), mElasticity(elasticity), mIsSensor(isSensor) {}

  void StaticShapePhysics::InitProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mIsSensor) cpShapeSetSensor(shape, true);
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

  StaticShapePhysics* StaticShapePhysics::Copy() {
    return new StaticShapePhysics(mFriction, mElasticity, mIsSensor);
  }

} // namespace game
