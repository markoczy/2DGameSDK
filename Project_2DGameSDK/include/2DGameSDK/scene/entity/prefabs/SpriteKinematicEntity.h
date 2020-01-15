/**
 * @file SpriteKinematicEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SpriteKinematicEntity class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SPRITE_KINEMATIC_ENTITY_H__
#define __SPRITE_KINEMATIC_ENTITY_H__

#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/KinematicEntity.h>

namespace game {
  /**
   * @brief Kinematic entity with single sprite render strategy
   * 
   */
  class GAMESDK_DLL SpriteKinematicEntity : public KinematicEntity {
  public:
    /**
     * @brief Constructs a new Sprite Kinematic Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param texture the render texture
     * @param shapes the physical shapes
     * @param isCollidable wether the object is collidable 
     */
    SpriteKinematicEntity(int type,
                          GameBase* game,
                          sf::Texture* texture,
                          std::vector<Shape<KinematicShapePhysics>*> shapes = std::vector<Shape<KinematicShapePhysics>*>(),
                          bool isCollidable = false);

    /**
     * @brief Sets the Size
     * 
     * @param size the new size
     */
    void SetSize(sf::Vector2f size);

  protected:
    SingleSpriteRenderStrategy* mSpriteRenderer = nullptr;
  };

} // namespace game

#endif
