#include <2DGameSDK/physics/shape/physics/DynamicShapePhysics.h>

namespace game {
  DynamicShapePhysics::DynamicShapePhysics(float mass, float friction, float elasticity, bool useDensityForMass) : mMass(mass), mFriction(friction), mElasticity(elasticity), mUseDensity(useDensityForMass) {}

  void DynamicShapePhysics::InitProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);

    if(mUseDensity) {
      cpShapeSetDensity(shape, mMass);
    } else {
      cpShapeSetMass(shape, mMass);
    }
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

  DynamicShapePhysics* DynamicShapePhysics::Copy() {
    return new DynamicShapePhysics(mMass, mFriction, mElasticity, mUseDensity);
  }
} // namespace game
