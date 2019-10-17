
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class SceneGraphNode;

  class GAMESDK_DLL Entity : public GameObject {
  public:
    Entity(int type);
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
    void SetGraphNode(game::SceneGraphNode* graphNode);

    void Transform(sf::Transform transform);
    void OnParentTransformed(sf::Transform accumulated);
    virtual void OnCollision(Entity* other, sf::Vector2f point);
    virtual void OnTickEnded();

  protected:
    // bool mIsCollidable = false;
    SceneGraphNode* mGraphNode = nullptr;

    virtual bool setTransform(sf::Transform transform);
    virtual bool transform(sf::Transform transform);
    virtual bool setAccumulatedTransform(sf::Transform accumulated);

  private:
    void onEntityTransformed();
  };

} // namespace game

#endif