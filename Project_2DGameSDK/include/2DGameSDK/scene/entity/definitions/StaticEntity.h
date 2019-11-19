#ifndef __STATIC_ENTITY_H__
#define __STATIC_ENTITY_H__

#include <vector>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/StaticShapeDefinition.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  class GAMESDK_DLL StaticEntity : public Entity {
  public:
    StaticEntity(int type,
                 Game* game,
                 std::vector<Shape<StaticShapeDefinition>*> shapes = std::vector<Shape<StaticShapeDefinition>*>(),
                 bool isCollidable = false);

    ~StaticEntity();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);
    virtual int OnWorldCollision(CollisionEventType type, Tile* tile, cpArbiter* arb);

  protected:
    bool mIsCollidable;
    std::vector<Shape<StaticShapeDefinition>*> mShapes;
    cpBody* mBody = nullptr;
  };
} // namespace game

#endif