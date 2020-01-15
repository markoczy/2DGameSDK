#ifndef __STATIC_ENTITY_H__
#define __STATIC_ENTITY_H__

#include <vector>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/physics/StaticShapePhysics.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  class GAMESDK_DLL StaticEntity : public Entity {
  public:
    StaticEntity(int type,
                 GameBase* game,
                 RenderStrategy* renderer,
                 std::vector<Shape<StaticShapePhysics>*> shapes = std::vector<Shape<StaticShapePhysics>*>(),
                 bool isCollidable = false);

    ~StaticEntity();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    virtual sf::Transform GetTransform();
    virtual sf::Transform GetAccumulatedTransform();
    virtual sf::Transform GetCombinedTransform();

    virtual RenderStrategy* GetRenderer();
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);
    virtual int OnWorldCollision(CollisionEventType type, Tile* tile, cpArbiter* arb);

  protected:
    RenderStrategy* mRenderer = nullptr;
    bool mIsCollidable;
    std::vector<Shape<StaticShapePhysics>*> mShapes;
    cpBody* mBody = nullptr;
    sf::Transform mTransform;

    virtual bool setTransform(sf::Transform transform);
  };
} // namespace game

#endif