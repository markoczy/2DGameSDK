
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

#include <chipmunk/chipmunk.h>

namespace game {
  class SceneGraphNode;
  class Game;

  class GAMESDK_DLL Entity : public GameObject {
  public:
    Entity(int type, Game* game);
    virtual ~Entity();

    virtual bool IsTransformable();
    virtual bool IsCollidable();
    virtual sf::Transform GetTransform();
    virtual sf::Transform GetAccumulatedTransform();
    virtual sf::Transform GetCombinedTransform();
    virtual sf::FloatRect GetAABB();
    virtual std::vector<sf::Vector2f> GetCollisionMask();

    void SetTransform(sf::Transform transform);

    /**
     * @brief Set the Graph Node object
     * 
     * @param graphNode The corresponding SceneGraphNode
     */
    void SetGraphNode(SceneGraphNode* graphNode);

    void Transform(sf::Transform transform);
    void OnParentTransformed(sf::Transform accumulated);
    virtual void OnCollision(Entity* other, sf::Vector2f point);
    virtual void OnTickEnded();

  protected:
    SceneGraphNode* mGraphNode = nullptr;

    virtual bool setTransform(sf::Transform transform);
    virtual bool transform(sf::Transform transform);
    virtual bool setAccumulatedTransform(sf::Transform accumulated);

  private:
    void onEntityTransformed();
  };

} // namespace game

#endif