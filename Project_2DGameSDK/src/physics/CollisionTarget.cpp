#include <2DGameSDK/physics/CollisionTarget.h>

namespace game {
  CollisionTarget::CollisionTarget(GameObject* target) : mTarget(target), mType(target->GetObjectType()) {}

  ObjectType CollisionTarget::GetType() {
    return mType;
  }

  GameObject* CollisionTarget::GetTarget() {
    return mTarget;
  }

} // namespace game
