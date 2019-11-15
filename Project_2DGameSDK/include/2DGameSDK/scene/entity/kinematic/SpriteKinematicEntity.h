/**
 * @file SpriteKinematicEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Sprite Transformable Entity class
 * @version 1.0
 * @date 2019-06-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __SPRITE_KINEMATIC_ENTITY_H__
#define __SPRITE_KINEMATIC_ENTITY_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/scene/entity/definitions/KinematicEntity.h>

namespace game {

  /**
   * @brief Simple specialisation of the KinematicEntity class. Does not
   *        do anything during OnTick().
   * 
   */
  class GAMESDK_DLL SpriteKinematicEntity : public KinematicEntity {
  public:
    /**
     * @brief Creates a new Sprite Transformable Entity object
     * 
     * @param type type The Entity Type (does not affect anything and is meant
     *        to be used freely to identify entities of some kind)
     * 
     * @param texture The Texture of the Entity
     */
    SpriteKinematicEntity(int type,
                          Game* game,
                          sf::Texture* texture,
                          std::vector<Shape*> shapes = std::vector<Shape*>(),
                          bool isCollidable = false);

    /**
     * @brief Destroys the Sprite Transformable Entity
     * 
     */
    ~SpriteKinematicEntity();

    virtual void SetSize(sf::Vector2f size);

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
  };

} // namespace game

#endif