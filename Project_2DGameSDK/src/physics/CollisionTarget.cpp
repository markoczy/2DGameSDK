#include <2DGameSDK/physics/CollisionTarget.h>

namespace game {

  CollisionTarget::CollisionTarget(void* target, ObjectType type) : mTarget(target), mType(type) {
  }

  ObjectType CollisionTarget::GetType() {
    return mType;
  }

  void* CollisionTarget::GetTarget() {
    return mTarget;
  }

} // namespace game
