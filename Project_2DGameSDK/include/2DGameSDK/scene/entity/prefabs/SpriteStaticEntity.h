/**
 * @file SpriteStaticEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SpriteStaticEntity class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SPRITE_STATIC_ENTITY_H__
#define __SPRITE_STATIC_ENTITY_H__

#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/StaticEntity.h>

namespace game {
  /**
   * @brief Static entity with single sprite render strategy
   * 
   */
  class GAMESDK_DLL SpriteStaticEntity : public StaticEntity {
  public:
    /**
     * @brief Constructs a new Sprite Static Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param texture the render texture
     * @param shapes the physical shapes
     * @param isCollidable wether the object is collidable
     */
    SpriteStaticEntity(int type,
                       GameBase* game,
                       sf::Texture* texture,
                       std::vector<Shape<StaticShapePhysics>*> shapes = std::vector<Shape<StaticShapePhysics>*>(),
                       bool isCollidable = false);

    /**
     * @brief Sets the Size
     * 
     * @param size the new size
     */
    void SetSize(sf::Vector2f size);

  private:
    SingleSpriteRenderStrategy* mSpecificRenderer = nullptr;
  };

} // namespace game

#endif
