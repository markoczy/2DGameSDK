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
    TransformableEntity(int type);

    /**
     * @brief Destroys the Transformable Entity object
     * 
     */
    ~TransformableEntity();

    /**
     * @brief Set the Graph Node object
     * 
     * @param graphNode The corresponding SceneGraphNode
     */
    void SetGraphNode(SceneGraphNode* graphNode);

    /**
     * @brief Retreives the reference to the SFML Transformable wich can
     *        be used to apply transformations to the Transformable Entity.
     * 
     * @return sf::Transformable* The Reference of the Transormable Object
     */
    virtual sf::Transformable* GetTransformable() = 0;

  protected:
    SceneGraphNode* mGraphNode = nullptr;
  };

} // namespace game

#endif