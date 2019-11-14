#include <2DGameSDK/physics/shape/definitions/DynamicShapeDefinition.h>

namespace game {
  DynamicShapeDefinition::DynamicShapeDefinition(Shape* shape, float mass, float friction, float elasticity, bool useDensityForMass) : mShape(shape), mMass(mass), mFriction(friction), mElasticity(elasticity), mUseDensity(useDensityForMass) {}

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
} // namespace game
