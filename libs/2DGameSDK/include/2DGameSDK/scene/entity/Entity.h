
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionEventType.h>

#include <chipmunk/chipmunk.h>

namespace game {
  class Tile;
  class SceneGraphNode;
  class Projectile;

  class GAMESDK_DLL Entity : public GameObject, public VisualObject {
  public:
    Entity(int type, GameBase* game);
    virtual ~Entity();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    /**
     * @brief Retreives the Type
     * 
     * @return int The GameObject Type
     */
    int GetType();

    int GetZIndex();

    virtual sf::Transform GetTransform();
    virtual sf::Transform GetAccumulatedTransform();
    virtual sf::Transform GetCombinedTransform();

    void SetZIndex(int zIndex);
    void SetTransform(sf::Transform transform);

    /**
     * @brief Set the Graph Node object
     * 
     * @param graphNode The corresponding SceneGraphNode
     */
    void SetGraphNode(SceneGraphNode* graphNode);

    void Transform(sf::Transform transform);
    void OnParentTransformed(sf::Transform accumulated);
    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);
    virtual int OnWorldCollision(CollisionEventType type, Tile* tile, cpArbiter* arb);
    virtual int OnProjectileCollision(CollisionEventType type, Projectile* tile, cpArbiter* arb);

    virtual void OnTickEnded();

  protected:
    int mType = 0;
    int mZIndex = constants::DEFAULT_ZINDEX_ENTITY;
    SceneGraphNode* mGraphNode = nullptr;

    virtual bool setTransform(sf::Transform transform);
    virtual bool transform(sf::Transform transform);
    virtual bool setAccumulatedTransform(sf::Transform accumulated);

  private:
    void onEntityTransformed();
  };

} // namespace game

#endif