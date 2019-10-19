/**
 * @file TransformableEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Transformable Entity class
 * @version 1.0
 * @date 2019-06-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __TRANSFORMABLE_ENTITY_H__
#define __TRANSFORMABLE_ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/Entity.h>

#include <SFML/Graphics.hpp>

namespace game {
  // Forward declaration
  class SceneGraphNode;

  /**
   * @brief Abstract class that defines an Entity that is Transformable and can
   *        be placed on the SceneGraph.
   * 
   */
  class GAMESDK_DLL TransformableEntity : public Entity {
  public:
    /**
     * @brief Creates a new Transformable Entity object
     * 
     * @param type type The Entity Type (does not affect anything and is meant
     *        to be used freely to identify entities of some kind)
     */
    TransformableEntity(int type, bool isCollidable = false);

    /**
     * @brief Destroys the Transformable Entity object
     * 
     */
    virtual ~TransformableEntity();

    virtual bool IsTransformable();
    virtual bool IsCollidable();

    virtual sf::Transform GetTransform();
    virtual sf::Transform GetAccumulatedTransform();
    virtual sf::Transform GetCombinedTransform();

    virtual void OnCollision(Entity* other, sf::Vector2f point);
    virtual void OnTickEnded();

  protected:
    sf::Transform mTransform;
    sf::Transform mAccTransform;
    sf::Transform mCombinedTransform;

    bool mIsCollidable;

    virtual bool setTransform(sf::Transform transform);
    virtual bool transform(sf::Transform transform);
    virtual bool setAccumulatedTransform(sf::Transform accumulated);
  };

} // namespace game

#endif