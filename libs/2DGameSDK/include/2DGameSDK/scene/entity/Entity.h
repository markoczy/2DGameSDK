/**
 * @file Entity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Entity class
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @brief Defines a simple Game Object (no transformations)
   * 
   * @see TransformableEntity
   * 
   */
  class GAMESDK_DLL Entity {
  public:
    /**
     * @brief Creates a new Entity object
     * 
     * @param type The Entity Type (does not affect anything and is meant
     *        to be used freely to identify entities of some kind)
     */
    Entity(int type);

    /**
     * @brief Destroys the Entity object
     * 
     */
    ~Entity();

    /**
     * @brief Retreives the Id
     * 
     * @return int The Identifier
     */
    int GetId();

    /**
     * @brief Retreives the Type
     * 
     * @return int The Entity Type
     */
    int GetType();

    /**
     * @brief Updates the Entity
     * 
     */
    virtual void Tick() = 0;

    /**
     * @brief Renders the entity
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    virtual void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default) = 0;

  protected:
    int mType;
    int mId;
  };

} // namespace game

#endif