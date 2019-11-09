#ifndef __STATIC_ENTITY_H__
#define __STATIC_ENTITY_H__

#include <vector>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/types/KinematicShape.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  class GAMESDK_DLL StaticEntity : public Entity {
  public:
    StaticEntity(int type,
                 Game* game,
                 std::vector<KinematicShape*> shapes = std::vector<KinematicShape*>(),
                 bool isCollidable = false);

    ~StaticEntity();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);

  protected:
    bool mIsCollidable;
    std::vector<KinematicShape*> mShapes;
    cpBody* mBody = nullptr;
  };
} // namespace game

#endif