#include <2DGameSDK/scene/entity/physical/PhysicalEntity.h>

namespace game {
  PhysicalEntity::PhysicalEntity(int type, Game* game, std::vector<DynamicShape*> shapes, bool isCollidable) : Entity(type, game), mShapes(shapes), mIsCollidable(isCollidable) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNew(1, 1));
    cpBodySetUserData(mBody, this);

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  PhysicalEntity::~PhysicalEntity() {}

  bool PhysicalEntity::IsKinematic() {
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

  int PhysicalEntity::OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb) {
    return 1;
  }

} // namespace game
