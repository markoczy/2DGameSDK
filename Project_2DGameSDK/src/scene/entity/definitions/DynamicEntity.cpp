#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {
  DynamicEntity::DynamicEntity(int type, GameBase* game, std::vector<Shape<DynamicShapeDefinition>*> shapes, bool isCollidable) : Entity(type, game), mIsCollidable(isCollidable), mShapes(shapes) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNew(0, 0));
    cpBodySetUserData(mBody, new CollisionTarget(this, ObjectType::Entity));

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  DynamicEntity::~DynamicEntity() {}

  bool DynamicEntity::IsKinematic() {
    return false;
  }

  bool DynamicEntity::IsCollidable() {
    return mIsCollidable;
  }

  void DynamicEntity::SetMass(float mass) {
    cpBodySetMass(mBody, mass);
  }

  void DynamicEntity::SetMoment(float moment) {
    cpBodySetMoment(mBody, moment);
  }

  void DynamicEntity::SetVelocity(cpVect velocity) {
    cpBodySetVelocity(mBody, velocity);
  }

  void DynamicEntity::SetForce(cpVect force) {
    cpBodySetForce(mBody, force);
  }

  void DynamicEntity::SetAngularVelocity(float angularVelocity) {
    cpBodySetAngularVelocity(mBody, angularVelocity);
  }

  void DynamicEntity::SetTorque(float torque) {
    cpBodySetTorque(mBody, torque);
  }

  int DynamicEntity::OnCollision(CollisionEventType, Entity*, cpArbiter*) {
    return 1;
  }

  int DynamicEntity::OnWorldCollision(CollisionEventType, Tile*, cpArbiter*) {
    return 1;
  }

} // namespace game
