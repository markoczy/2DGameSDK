#ifndef __COLLISION_TARGET_H__
#define __COLLISION_TARGET_H__

#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/core/GameObject.h>

namespace game {
  class CollisionTarget {
  public:
    CollisionTarget(void* target, ObjectType type);
    ObjectType GetType();
    void* GetTarget();

  private:
    void* mTarget;
    ObjectType mType;
  };
} // namespace game

#endif