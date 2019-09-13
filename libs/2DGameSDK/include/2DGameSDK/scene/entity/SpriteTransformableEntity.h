/**
 * @file SpriteTransformableEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Sprite Transformable Entity class
 * @version 1.0
 * @date 2019-06-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __SPRITE_TRANSFORMABLE_ENTITY_H__
#define __SPRITE_TRANSFORMABLE_ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/TransformableEntity.h>
#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @brief Simple specialisation of the TransformableEntity class. Does not
   *        do anything during Tick().
   * 
   */
  class GAMESDK_DLL SpriteTransformableEntity : public TransformableEntity {
  public:
    /**
     * @brief Creates a new Sprite Transformable Entity object
     * 
     * @param type type The Entity Type (does not affect anything and is meant
     *        to be used freely to identify entities of some kind)
     * 
     * @param texture The Texture of the Entity
     */
    SpriteTransformableEntity(int type, sf::Texture* texture);

    /**
     * @brief Destroys the Sprite Transformable Entity
     * 
     */
    ~SpriteTransformableEntity();

    /**
     * @brief Updates the Entity
     * 
     */
    virtual void Tick();

    /**
     * @brief Renders the Entity
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    /**
     * @brief Retreives the reference to the SFML Transformable wich can
     *        be used to apply transformations to the Transformable Entity.
     * 
     * @return sf::Transformable* The Reference of the Transormable Object
     */
    sf::Transformable* GetTransformable();

    virtual sf::FloatRect GetAABB();

  protected:
    sf::Sprite mSprite;
  };

} // namespace game

#endif