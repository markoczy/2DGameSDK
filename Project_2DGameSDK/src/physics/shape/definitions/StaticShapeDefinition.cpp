#include <2DGameSDK/physics/shape/definitions/StaticShapeDefinition.h>

namespace game {

  StaticShapeDefinition::StaticShapeDefinition(Shape* shape, float friction, float elasticity, bool isSensor) : mShape(shape), mFriction(friction), mElasticity(elasticity), mIsSensor(isSensor) {}

  void StaticShapeDefinition::InitProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mIsSensor) cpShapeSetSensor(shape, true);
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

} // namespace game
