#include <2DGameSDK/scene/entity/physical/PhysicalEntity.h>

namespace game {
  PhysicalEntity::PhysicalEntity(int type, Game* game, bool isCollidable, float mass, float moment) : Entity(type, game), mIsCollidable(isCollidable) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNew(mass, moment));
    cpBodySetUserData(mBody, this);
  }

  PhysicalEntity::~PhysicalEntity() {}

  bool PhysicalEntity::IsTransformable() {
    return false;
  }

  bool PhysicalEntity::IsCollidable() {
    return mIsCollidable;
  }

  void PhysicalEntity::SetMass(float mass) {
    cpBodySetMass(mBody, mass);
  }

  void PhysicalEntity::SetMoment(float moment) {
    cpBodySetMoment(mBody, moment);
  }

  void PhysicalEntity::SetVelocity(cpVect velocity) {
    cpBodySetVelocity(mBody, velocity);
  }

  void PhysicalEntity::SetForce(cpVect force) {
    cpBodySetForce(mBody, force);
  }

  void PhysicalEntity::SetAngularVelocity(float angularVelocity) {
    cpBodySetAngularVelocity(mBody, angularVelocity);
  }

  void PhysicalEntity::SetTorque(float torque) {
    cpBodySetTorque(mBody, torque);
  }

} // namespace game
