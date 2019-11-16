#include <2DGameSDK/physics/shape/definitions/DynamicShapeDefinition.h>

namespace game {
  DynamicShapeDefinition::DynamicShapeDefinition(float mass, float friction, float elasticity, bool useDensityForMass) : mMass(mass), mFriction(friction), mElasticity(elasticity), mUseDensity(useDensityForMass) {}

  void DynamicShapeDefinition::InitProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);

    if(mUseDensity) {
      cpShapeSetDensity(shape, mMass);
    } else {
      cpShapeSetMass(shape, mMass);
    }
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

  DynamicShapeDefinition* DynamicShapeDefinition::Copy() {
    return new DynamicShapeDefinition(mMass, mFriction, mElasticity, mUseDensity);
  }
} // namespace game
