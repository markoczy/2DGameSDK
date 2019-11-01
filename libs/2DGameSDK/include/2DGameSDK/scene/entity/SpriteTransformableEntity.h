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

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/sensor/RectangleSensorShape.h>
#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  /**
   * @brief Simple specialisation of the TransformableEntity class. Does not
   *        do anything during OnTick().
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
    SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, bool isCollidable = false);

    SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, std::vector<Shape*> shapes);

    /**
     * @brief Destroys the Sprite Transformable Entity
     * 
     */
    ~SpriteTransformableEntity();

    /**
     * @brief Updates the Entity
     * 
     */
    virtual void OnTick();

    virtual void OnTickEnded();

    /**
     * @brief Renders the Entity
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

  protected:
    sf::Sprite mSprite;
    std::vector<Shape*> mShapes;
  };

} // namespace game

#endif