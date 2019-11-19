
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionEventType.h>
#include <2DGameSDK/world/tilemap/Tile.h>

#include <chipmunk/chipmunk.h>

namespace game {
  class SceneGraphNode;
  class Game;

  class GAMESDK_DLL Entity : public GameObject {
  public:
    Entity(int type, Game* game);
    virtual ~Entity();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    /**
     * @brief Retreives the Type
     * 
     * @return int The GameObject Type
     */
    int GetType();

    virtual sf::Transform GetTransform();
    virtual sf::Transform GetAccumulatedTransform();
    virtual sf::Transform GetCombinedTransform();

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

    /**
     * @brief Updates the Entity
     * 
     */
    virtual void OnTick() = 0;

    virtual void OnTickEnded();

    /**
     * @brief Renders the Entity
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default) = 0;

  protected:
    int mType = 0;
    SceneGraphNode* mGraphNode = nullptr;

    virtual bool setTransform(sf::Transform transform);
    virtual bool transform(sf::Transform transform);
    virtual bool setAccumulatedTransform(sf::Transform accumulated);

  private:
    void onEntityTransformed();
  };

} // namespace game

#endif