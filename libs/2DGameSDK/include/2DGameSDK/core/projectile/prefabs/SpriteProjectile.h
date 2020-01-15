/**
 * @file SpriteProjectile.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SpriteProjectile
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SPRITE_PROJECTILE_H__
#define __SPRITE_PROJECTILE_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/projectile/Projectile.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Defines a projectile that is rendered as single sprite
   * 
   */
  class GAMESDK_DLL SpriteProjectile : public Projectile {
  public:
    /**
     * @brief Constructs a new Sprite Projectile
     * 
     * @param game the game
     * @param type type the user defined projectile type
     * @param texture the render texture
     * @param shape the physical shape
     * @param start the spawn point in world coordinates
     * @param velocity the velocity vector
     */
    SpriteProjectile(GameBase* game, int type, sf::Texture* texture, Shape<KinematicShapePhysics>* shape, sf::Transform start, sf::Vector2f velocity);
  };
} // namespace game

#endif