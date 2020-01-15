
/**
 * @file Entity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Entity class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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

  /**
   * @brief Generic Entity
   * 
   */
  class GAMESDK_DLL Entity : public GameObject, public VisualObject {
  public:
    /**
     * @brief Constructs a new Entity
     * 
     * @param type the user defined type
     * @param game the game
     */
    Entity(int type, GameBase* game);

    /**
     * @brief Destroys the Entity
     * 
     */
    virtual ~Entity();

    /**
     * @brief Retreives wether the object is kinematic
     * 
     * @return bool is kinematic
     */
    virtual bool IsKinematic();

    /**
     * @brief Retreives wether the object is collidable
     * 
     * @return bool is collidable
     */
    virtual bool IsCollidable();

    /**
     * @brief Retreives the Type
     * 
     * @return int The GameObject Type
     */
    int GetType();

    /**
     * @brief Retreive the Z Index
     * 
     * @return int the Z Index
     */
    int GetZIndex();

    /**
     * @brief Retreives the current Transform
     * 
     * @return sf::Transform the transform
     */
    virtual sf::Transform GetTransform();

    /**
     * @brief Retreives the current Accumulated Transform
     * 
     * @return sf::Transform the accumulated transform
     */
    virtual sf::Transform GetAccumulatedTransform();

    /**
     * @brief Retreives the current Combined Transform (current*accumulated)
     * 
     * @return sf::Transform 
     */
    virtual sf::Transform GetCombinedTransform();

    /**
     * @brief Sets the Z Index
     * 
     * @param zIndex the new Z Index
     */
    void SetZIndex(int zIndex);
    void SetTransform(sf::Transform transform);

    /**
     * @brief Set the Graph Node object
     * 
     * @param graphNode The corresponding SceneGraphNode
     */
    void SetGraphNode(SceneGraphNode* graphNode);

    /**
     * @brief Sets the entity's tranformation
     * 
     * @param transform the new transfomration
     */
    void Transform(sf::Transform transform);

    /**
     * @brief Updates accumulated transformation
     * 
     * @param accumulated 
     */
    void OnParentTransformed(sf::Transform accumulated);

    /**
     * @brief Callback when entity has collided with another entity
     * 
     * @param type collision event type
     * @param other the other entity
     * @param arb the chipmunk arbiter
     * @return int the collision return value
     */
    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);

    /**
     * @brief Callback when entity has collided with another entity
     * 
     * @param type collision event type
     * @param other the other entity
     * @param arb the chipmunk arbiter
     * @return int the collision return value
     */
    virtual int OnWorldCollision(CollisionEventType type, Tile* tile, cpArbiter* arb);

    /**
     * @brief Callback when entity has collided with a projectile
     * 
     * @param type collision event type
     * @param projectile the projectile
     * @param arb the chipmunk arbiter
     * @return int the collision return value
     */
    virtual int OnProjectileCollision(CollisionEventType type, Projectile* projectile, cpArbiter* arb);

    /**
     * @brief Callback after update
     * 
     */
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