/**
 * @file SpriteDynamicEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SpriteDynamicEntity class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SPRITE_DYNAMIC_ENTITY_H__
#define __SPRITE_DYNAMIC_ENTITY_H__

#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {
  /**
   * @brief Dynamic entity with single sprite render strategy
   * 
   */
  class GAMESDK_DLL SpriteDynamicEntity : public DynamicEntity {
  public:
    /**
     * @brief Constructs a new Sprite Dynamic Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param texture the render texture
     * @param shapes the physical shapes
     * @param isCollidable wether the object is collidable
     */
    SpriteDynamicEntity(int type,
                        GameBase* game,
                        sf::Texture* texture,
                        std::vector<Shape<DynamicShapePhysics>*> shapes = std::vector<Shape<DynamicShapePhysics>*>(),
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
